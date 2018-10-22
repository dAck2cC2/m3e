

#define LOG_TAG "audio_dump"
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
#include <cutils/threads.h>
#include <cutils/properties.h>

#include <hardware/hardware.h>
#include <system/audio.h>
#include <hardware/audio.h>

#include <utils/ADebugExt.h>
#include <utils/Errors.h>

using namespace android;

#define AUDIO_DUMP_FILE_NAME "audio_dump.pcm"

struct stub_audio_device {
    struct audio_hw_device device;
};

struct stub_stream_out {
    struct audio_stream_out stream;
	int64_t last_write_time_us;
	uint32_t                sample_rate;
	audio_channel_mask_t    channel_mask;
	audio_format_t          format;
	uint32_t                latency_ms;
	size_t                  buffer_size;
	FILE* fd;
};

struct stub_stream_in {
    struct audio_stream_in stream;
};

static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
	struct stub_stream_out * out = (struct stub_stream_out *)stream;

	if (out) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sample_rate);
		return (out->sample_rate);
	} else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return (44100);
	}
}

static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    ALOGV("[0x%X]out_set_sample_rate: %d", stream, rate);
    return -ENOSYS;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
	struct stub_stream_out * out = (struct stub_stream_out *)stream;

	if (out) {
		ALOGV("[0x%X]%s: %d", out, __FUNCTION__, out->buffer_size);
		return (out->buffer_size);
	} else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return 4096;
	}
}

static audio_channel_mask_t out_get_channels(const struct audio_stream *stream)
{
	struct stub_stream_out * out = (struct stub_stream_out *)stream;
	if (out) {
		ALOGV("[0x%X]%s: 0x%X", out, __FUNCTION__, out->channel_mask);
		return (out->channel_mask);
	} else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return AUDIO_CHANNEL_OUT_STEREO;
	}
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
	struct stub_stream_out * out = (struct stub_stream_out *)stream;

	if (out) {
		ALOGV("[0x%X]%s: 0x%X", out, __FUNCTION__, out->format);
		return (out->format);
	}
	else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return AUDIO_FORMAT_PCM_16_BIT;
	}
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
    ALOGV("[0x%X]%s: 0x%X", stream, __FUNCTION__, format);
    return -ENOSYS;
}

static int out_standby(struct audio_stream *stream)
{
    ALOGV("[0x%X]%s", stream, __FUNCTION__);

	struct stub_stream_out * out = (struct stub_stream_out *)stream;
	out->last_write_time_us = 0; //unnecessary as a stale write time has same effect

    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    ALOGV("[0x%X]%s: %d", stream, __FUNCTION__, fd);
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    ALOGV("[0x%X]%s: %s", stream, __FUNCTION__, kvpairs);
    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    ALOGV("[0x%X]%s", stream, __FUNCTION__);
    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
	struct stub_stream_out * out = (struct stub_stream_out *)stream;

	if (out) {
		ALOGV("[0x%X]%s: %d ms", out, __FUNCTION__, out->latency_ms);
		return (out->latency_ms);
	} else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return 0;
	}
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    ALOGV("[0x%X]%s: Left:%f Right:%f", stream, __FUNCTION__, left, right);
    return 0;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    ALOGV("[0x%X]%s: bytes: 0x%X, %d", stream, __FUNCTION__, buffer, bytes);

	if (!buffer || bytes <= 0) {
		ALOGV("%s invalid input data !", __FUNCTION__);
		return -1;
	}

	struct stub_stream_out * out = (struct stub_stream_out *)stream;
	if (!out || !out->fd) {
		ALOGV("%s no output file !", __FUNCTION__);
		return -1;
	}

	ssize_t w = fwrite(buffer, 1, bytes, out->fd);


	//struct timespec t = { .tv_sec = 0, .tv_nsec = 0 };
	struct timespec t;
	memset(&t, 0x00, sizeof(t));
	clock_gettime(CLOCK_MONOTONIC, &t);
	const int64_t now = (t.tv_sec * 1000000000LL + t.tv_nsec) / 1000;
	const int64_t elapsed_time_since_last_write = now - out->last_write_time_us;
	int64_t sleep_time = bytes * 1000000LL / audio_stream_out_frame_size(stream) /
		out_get_sample_rate(&stream->common) - elapsed_time_since_last_write;
	if (sleep_time > 0) {
		usleep(sleep_time);
	}
	else {
		// we don't sleep when we exit standby (this is typical for a real alsa buffer).
		sleep_time = 0;
	}
	out->last_write_time_us = now + sleep_time;
	// last_write_time_us is an approximation of when the (simulated) alsa
	// buffer is believed completely full. The usleep above waits for more space
	// in the buffer, but by the end of the sleep the buffer is considered
	// topped-off.
	//
	// On the subsequent out_write(), we measure the elapsed time spent in
	// the mixer. This is subtracted from the sleep estimate based on frames,
	// thereby accounting for drain in the alsa buffer during mixing.
	// This is a crude approximation; we don't handle underruns precisely.

    return w;
}

static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    *dsp_frames = 0;
    ALOGV("[0x%X]%s: dsp_frames: %p", stream, __FUNCTION__, dsp_frames);
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("[0x%X]%s: %p", stream, __FUNCTION__, effect);
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("[0x%X]out_remove_audio_effect: %p", stream, effect);
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
    *timestamp = 0;
    ALOGV("[0x%X]%s: %ld", stream, __FUNCTION__, (long int)(*timestamp));
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
	ALOGV("%s dev: 0x%X", __FUNCTION__, dev);
	ALOGV("%s handle: %d", __FUNCTION__, handle);
	ALOGV("%s devices: %d", __FUNCTION__, devices);
	if (config) {
		ALOGV("%s config->sample_rate : %d", __FUNCTION__, config->sample_rate);
		ALOGV("%s config->channel_mask: 0x%X", __FUNCTION__, config->channel_mask);
		ALOGV("%s config->format      : 0x%X", __FUNCTION__, config->format);
		ALOGV("%s config->frame_count : %d", __FUNCTION__, config->frame_count);
	}
	ALOGV("%s flags: 0x%X", __FUNCTION__, flags);
	if (address) {
		ALOGV("%s address: %s", __FUNCTION__, address);
	}

	int ret = -EEXIST;
	struct stub_audio_device *ladev = (struct stub_audio_device *)dev;
	struct stub_stream_out *out = (struct stub_stream_out *)calloc(1, sizeof(struct stub_stream_out));
	if (!out) return -ENOMEM;

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

	out->sample_rate = 44100;
	out->channel_mask = AUDIO_CHANNEL_OUT_STEREO;
	out->format = AUDIO_FORMAT_PCM_16_BIT;
	out->latency_ms = 0; // property_get_int32("audio.device.buffer.ms", 50);
	out->buffer_size = 4096; //(2 * out->sample_rate * out->latency_ms) / 1000;

	out->fd = fopen(AUDIO_DUMP_FILE_NAME, "w");
	if (out->fd == NULL) {
		ALOGV("%s failed to open dump file %s", __FUNCTION__, AUDIO_DUMP_FILE_NAME);
		goto err_open;
	}

    *stream_out = &out->stream;

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

	struct stub_audio_device *ladev = (struct stub_audio_device *)dev;
	struct stub_stream_out   *out   = (struct stub_stream_out *)stream;

	if (out->fd) {
		fclose(out->fd);
		out->fd = NULL;
	}

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
	audio_input_flags_t flags,
	const char *address,
	audio_source_t source)
{
	ALOGV("adev_open_input_stream dev      :0x%X", dev);
	ALOGV("adev_open_input_stream handle   :%d",   handle);
	ALOGV("adev_open_input_stream devices  :%d",   devices);
	if (config) {
		ALOGV("adev_open_input_stream config->sample_rate :%d",    config->sample_rate);
		ALOGV("adev_open_input_stream config->channel_mask:0x%X",  config->channel_mask);
		ALOGV("adev_open_input_stream config->format      :0x%X",  config->format);
		ALOGV("adev_open_input_stream config->frame_count :%d",    config->frame_count);
	}
	ALOGV("adev_open_input_stream stream_in:0x%X", stream_in);
	ALOGV("adev_open_input_stream flags    :0x%X", flags);
	if (address) {
		ALOGV("adev_open_input_stream address :%s", address);
	}
	ALOGV("adev_open_input_stream source   :%d", source);


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
    adev->device.set_master_volume = NULL;
    adev->device.get_master_volume = NULL;
    adev->device.set_master_mute = NULL;
    adev->device.get_master_mute = NULL;
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
