

#define LOG_TAG "audio_openal"
//#define LOG_NDEBUG 0

#include <errno.h>
#if defined(__APPLE__)
#include <stdlib.h>
#else
#include <malloc.h>
#endif
//#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#include <cutils/log.h>

#include <hardware/hardware.h>
#include <system/audio.h>
#include <hardware/audio.h>

#include <cutils/threads.h>

#include <utils/ADebugExt.h>
#include <utils/Errors.h>

#include <al.h>
#include <alc.h>

using namespace android;

#define OPENAL_SINK_BUFFER_COUNT  (4)
#define OPENAL_SINK_BUFFER_MS     (100)

struct OPENAL_SINK_CTL {
	int      inited;
	ALuint   src;
	ALuint   buf[OPENAL_SINK_BUFFER_COUNT];
	ALenum   fmt;
	ALsizei  frq;
	int      bits;
	uint32_t size;
	uint32_t pos;
};
static OPENAL_SINK_CTL mAudioSink;

static status_t createSink()
{
	ALOGD("createSink");

	memset(&mAudioSink, 0x00, sizeof(mAudioSink));

	// First the standard open-device, create-context, set-context..
	ALCdevice* dev = alcOpenDevice(NULL);
	CHECK_PTR_EXT(dev, NO_MEMORY);

	ALCcontext* ctx = alcCreateContext(dev, NULL);
	CHECK_PTR_EXT(ctx, NO_MEMORY);

	alcMakeContextCurrent(ctx);

	// Generate the buffers and sources
	alGenBuffers(OPENAL_SINK_BUFFER_COUNT, mAudioSink.buf);
	alGenSources(1, &(mAudioSink.src));
	CHECK_IS_EXT((AL_NO_ERROR == alGetError()), BAD_VALUE);

	// Get the sample frequency (32-bit little-endian)
	mAudioSink.frq = 44100;

	// Now convert the given channel count and bit depth into an OpenAL format.
	mAudioSink.fmt  = AL_FORMAT_STEREO16;
	mAudioSink.bits = 16;

	// Calculate buffer size
	mAudioSink.size = ((mAudioSink.frq * OPENAL_SINK_BUFFER_MS) / 1000) * (mAudioSink.bits / 8);

	ALOGD("create frameCount: %d", (mAudioSink.frq * OPENAL_SINK_BUFFER_MS) / 1000);
	ALOGD("create latency: %d", OPENAL_SINK_BUFFER_MS);
	ALOGD("create format: %d", mAudioSink.fmt);
	ALOGD("create frequency: %d", mAudioSink.frq);
	ALOGD("create bitsPerSample: %d", mAudioSink.bits);
	ALOGD("create bufferSize: %d", mAudioSink.size);

	mAudioSink.inited = 1;

	RETURN(OK);
}

static void closeSink()
{
	if (mAudioSink.src) {
		alDeleteSources(1, &mAudioSink.src);
		alDeleteBuffers(OPENAL_SINK_BUFFER_COUNT, mAudioSink.buf);
		memset(&mAudioSink, 0x00, sizeof(mAudioSink));
	}

	ALCcontext * ctx = alcGetCurrentContext();
	if (ctx) {
		ALCdevice * dev = alcGetContextsDevice(ctx);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(ctx);
		alcCloseDevice(dev);
	}

	return;
}

struct stub_audio_device {
    struct audio_hw_device device;
};

struct stub_stream_out {
    struct audio_stream_out stream;
    int64_t last_write_time_us;
};

struct stub_stream_in {
    struct audio_stream_in stream;
    int64_t last_read_time_us;
};

static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
    return 44100;
}

static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    ALOGV("out_set_sample_rate: %d", 0);
    return -ENOSYS;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
    ALOGV("out_get_buffer_size: %d", 4096);
    return 4096;
}

static audio_channel_mask_t out_get_channels(const struct audio_stream *stream)
{
    ALOGV("out_get_channels");
    return AUDIO_CHANNEL_OUT_STEREO;
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
    ALOGV("out_get_format");
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
    ALOGV("out_set_format: %d",format);
    return -ENOSYS;
}

static int out_standby(struct audio_stream *stream)
{
    ALOGV("out_standby");
    // out->last_write_time_us = 0; unnecessary as a stale write time has same effect
    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    ALOGV("out_dump");
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    ALOGV("out_set_parameters");
    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    ALOGV("out_get_parameters");
    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
    ALOGV("out_get_latency");
    return OPENAL_SINK_BUFFER_MS;
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    ALOGV("out_set_volume: Left:%f Right:%f", left, right);
    return 0;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    ALOGV("out_write: bytes: %d", bytes);

	CHECK_IS_EXT((mAudioSink.inited == 1), 0);
	CHECK_IS_EXT((mAudioSink.size > 0), 0);

	static struct {
		ALint  cnt;
		ALuint buf[OPENAL_SINK_BUFFER_COUNT];
	} s_free = { 0 };

	/* Get relevant source info */
	ALint state = 0;
	alGetSourcei(mAudioSink.src, AL_SOURCE_STATE, &state);
	if (AL_INITIAL == state) {
		for (int i = 0; i < OPENAL_SINK_BUFFER_COUNT; ++i) {
			s_free.buf[i] = mAudioSink.buf[i];
		}
		s_free.cnt = OPENAL_SINK_BUFFER_COUNT;
	}
	else {
		while (s_free.cnt <= 0) {
			alGetSourcei(mAudioSink.src, AL_BUFFERS_PROCESSED, &s_free.cnt);
			alSourceUnqueueBuffers(mAudioSink.src, s_free.cnt, s_free.buf);
			CHECK_IS_EXT((AL_NO_ERROR == alGetError()), 0);

			if (0 == s_free.cnt) {
				//ALOGV("wait for playback ...");
				usleep(100);
			}
		}
	}

	size_t nsrc = bytes > mAudioSink.size ? mAudioSink.size : bytes;

	alBufferData(s_free.buf[s_free.cnt - 1], mAudioSink.fmt, buffer, nsrc, mAudioSink.frq);
	alSourceQueueBuffers(mAudioSink.src, 1, &s_free.buf[s_free.cnt - 1]);
	s_free.cnt--;

	mAudioSink.pos += nsrc;

	if ((state != AL_PLAYING) && (state != AL_PAUSED)) {
		ALint queued = 0;

		/* If no buffers are queued, playback is finished */
		alGetSourcei(mAudioSink.src, AL_BUFFERS_QUEUED, &queued);
		if (queued == 0) {
			return 0;
		}

		alSourcePlay(mAudioSink.src);
		CHECK_IS_EXT((AL_NO_ERROR == alGetError()), 0);
	}

    return bytes;
}

static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    *dsp_frames = 0;
    ALOGV("out_get_render_position: dsp_frames: %p", dsp_frames);
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("out_add_audio_effect: %p", effect);
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("out_remove_audio_effect: %p", effect);
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
    *timestamp = 0;
    ALOGV("out_get_next_write_timestamp: %ld", (long int)(*timestamp));
    return -EINVAL;
}

/** audio_stream_in implementation **/
static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    ALOGV("in_get_sample_rate");
    return 8000;
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    ALOGV("in_set_sample_rate: %d", rate);
    return -ENOSYS;
}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    ALOGV("in_get_buffer_size: %d", 320);
    return 320;
}

static audio_channel_mask_t in_get_channels(const struct audio_stream *stream)
{
    ALOGV("in_get_channels: %d", AUDIO_CHANNEL_IN_MONO);
    return AUDIO_CHANNEL_IN_MONO;
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    return -ENOSYS;
}

static int in_standby(struct audio_stream *stream)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream;
    in->last_read_time_us = 0;
    return 0;
}

static int in_dump(const struct audio_stream *stream, int fd)
{
    return 0;
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    return 0;
}

static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
    return strdup("");
}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    return 0;
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    ALOGV("in_read: bytes %d", bytes);

    /* XXX: fake timing for audio input */
    struct stub_stream_in *in = (struct stub_stream_in *)stream;
    //struct timespec t = { .tv_sec = 0, .tv_nsec = 0 };
	struct timespec t;
	memset(&t, 0x00, sizeof(t));
    clock_gettime(CLOCK_MONOTONIC, &t);
    const int64_t now = (t.tv_sec * 1000000000LL + t.tv_nsec) / 1000;

    // we do a full sleep when exiting standby.
    const bool standby = in->last_read_time_us == 0;
    const int64_t elapsed_time_since_last_read = standby ?
            0 : now - in->last_read_time_us;
    int64_t sleep_time = bytes * 1000000LL / audio_stream_in_frame_size(stream) /
            in_get_sample_rate(&stream->common) - elapsed_time_since_last_read;
    if (sleep_time > 0) {
        usleep(sleep_time);
    } else {
        sleep_time = 0;
    }
    in->last_read_time_us = now + sleep_time;
    // last_read_time_us is an approximation of when the (simulated) alsa
    // buffer is drained by the read, and is empty.
    //
    // On the subsequent in_read(), we measure the elapsed time spent in
    // the recording thread. This is subtracted from the sleep estimate based on frames,
    // thereby accounting for fill in the alsa buffer during the interim.
    memset(buffer, 0, bytes);
    return bytes;
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
    return 0;
}

static int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    return 0;
}

static int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    return 0;
}

static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out,
                                   const char *address)
{
    ALOGV("adev_open_output_stream...");

    struct stub_audio_device *ladev = (struct stub_audio_device *)dev;
    struct stub_stream_out *out;
    int ret;

    out = (struct stub_stream_out *)calloc(1, sizeof(struct stub_stream_out));
    if (!out)
        return -ENOMEM;

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;

    *stream_out = &out->stream;

	createSink();

    return 0;

err_open:
    free(out);
    *stream_out = NULL;
    return ret;
}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
    ALOGV("adev_close_output_stream...");
	
	closeSink();

    free(stream);
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    ALOGV("adev_set_parameters");
    return -ENOSYS;
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    ALOGV("adev_get_parameters");
    return strdup("");
}

static int adev_init_check(const struct audio_hw_device *dev)
{
    ALOGV("adev_init_check");
	return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_voice_volume: %f", volume);
    return -ENOSYS;
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_master_volume: %f", volume);
    return -ENOSYS;
}

static int adev_get_master_volume(struct audio_hw_device *dev, float *volume)
{
    ALOGV("adev_get_master_volume: %f", *volume);
    return -ENOSYS;
}

static int adev_set_master_mute(struct audio_hw_device *dev, bool muted)
{
    ALOGV("adev_set_master_mute: %d", muted);
    return -ENOSYS;
}

static int adev_get_master_mute(struct audio_hw_device *dev, bool *muted)
{
    ALOGV("adev_get_master_mute: %d", *muted);
    return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode)
{
    ALOGV("adev_set_mode: %d", mode);
    return 0;
}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    ALOGV("adev_set_mic_mute: %d",state);
    return -ENOSYS;
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    ALOGV("adev_get_mic_mute");
    return -ENOSYS;
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
    ALOGV("adev_get_input_buffer_size: %d", 320);
    return 320;
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in,
                                  audio_input_flags_t flags  ,
                                  const char *address  ,
                                  audio_source_t source  )
{
    ALOGV("adev_open_input_stream...");

    struct stub_audio_device *ladev = (struct stub_audio_device *)dev;
    struct stub_stream_in *in;
    int ret;

    in = (struct stub_stream_in *)calloc(1, sizeof(struct stub_stream_in));
    if (!in)
        return -ENOMEM;

    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;

    *stream_in = &in->stream;
    return 0;

err_open:
    free(in);
    *stream_in = NULL;
    return ret;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *in)
{
    ALOGV("adev_close_input_stream...");
    return;
}

static int adev_dump(const audio_hw_device_t *device, int fd)
{
    ALOGV("adev_dump");
    return 0;
}

static int adev_close(hw_device_t *device)
{
    ALOGV("adev_close");
    free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    ALOGV("adev_open: %s", name);

    struct stub_audio_device *adev;
    int ret;

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
        return -EINVAL;

    adev = (struct stub_audio_device *)calloc(1, sizeof(struct stub_audio_device));
    if (!adev)
        return -ENOMEM;

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
    adev->device.get_master_volume = adev_get_master_volume;
    adev->device.set_master_mute = adev_set_master_mute;
    adev->device.get_master_mute = adev_get_master_mute;
    adev->device.set_mode = adev_set_mode;
    adev->device.set_mic_mute = adev_set_mic_mute;
    adev->device.get_mic_mute = adev_get_mic_mute;
    adev->device.set_parameters = adev_set_parameters;
    adev->device.get_parameters = adev_get_parameters;
    adev->device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->device.open_output_stream = adev_open_output_stream;
    adev->device.close_output_stream = adev_close_output_stream;
    adev->device.open_input_stream = adev_open_input_stream;
    adev->device.close_input_stream = adev_close_input_stream;
    adev->device.dump = adev_dump;

    *device = &adev->device.common;

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    /*.open = */adev_open,
};

#ifdef __cplusplus
extern "C"
#endif
#if defined(_MSC_VER)
__declspec(dllexport)
#endif
struct audio_module HAL_MODULE_INFO_SYM = {
    /*.common =*/ {
        /*.tag =*/ HARDWARE_MODULE_TAG,
        /*.module_api_version =*/ AUDIO_MODULE_API_VERSION_0_1,
        /*.hal_api_version =*/ HARDWARE_HAL_API_VERSION,
        /*.id =*/ AUDIO_HARDWARE_MODULE_ID,
        /*.name =*/ "Default audio HW HAL",
        /*.author =*/ "The Android Open Source Project",
        /*.methods =*/ &hal_module_methods,
    },
};
