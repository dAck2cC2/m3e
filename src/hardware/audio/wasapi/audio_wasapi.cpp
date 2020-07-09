

#define LOG_TAG "audio_dump"
//#define LOG_NDEBUG 0

#define INITGUID

#include <errno.h>
#include <malloc.h>
#include <stdint.h>
#include <sys/time.h>

#include <cutils/log.h>
#include <cutils/threads.h>
#include <cutils/properties.h>

#include <hardware/hardware.h>
#include <system/audio.h>
#include <hardware/audio.h>

#include <utils/Errors.h>
#include <utils/RefBase.h>

#include <mmdeviceapi.h>
#include <audioclient.h>
#include <devpropdef.h>
#include <mmreg.h>

#define REFTIME_PER_SEC ((REFERENCE_TIME)10000000)


DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xbcde0395, 0xe52f, 0x467c, 0x8e, 0x3d, 0xc4, 0x57, 0x92, 0x91, 0x69, 0x2e);
DEFINE_GUID(IID_IMMDeviceEnumerator, 0xa95664d2, 0x9614, 0x4f35, 0xa7, 0x46, 0xde, 0x8d, 0xb6, 0x36, 0x17, 0xe6);
DEFINE_GUID(IID_IAudioClient, 0x1cb9ad4c, 0xdbfa, 0x4c32, 0xb1, 0x78, 0xc2, 0xf5, 0x68, 0xa7, 0x03, 0xb2);
DEFINE_GUID(IID_IAudioRenderClient, 0xf294acfc, 0x3146, 0x4483, 0xa7, 0xbf, 0xad, 0xdc, 0xa7, 0xc2, 0x60, 0xe2);
DEFINE_GUID(IID_IAudioCaptureClient, 0xc8adbd64, 0xe71e, 0x48a0, 0xa4, 0xde, 0x18, 0x5c, 0x39, 0x5c, 0xd3, 0x17);


using namespace android;

/* Scales the given value using 64-bit integer math, ceiling the result. */
static inline uint64_t ScaleCeil(uint64_t val, uint64_t new_scale, uint64_t old_scale)
{
	return (val * new_scale + old_scale - 1) / old_scale;
}

static bool MakeExtensible(WAVEFORMATEXTENSIBLE* out, const WAVEFORMATEX* in)
{
	memset(out, 0, sizeof(*out));
	if (in->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
		*out = *(const WAVEFORMATEXTENSIBLE*)in;
	else if (in->wFormatTag == WAVE_FORMAT_PCM)
	{
		out->Format = *in;
		out->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		out->Format.cbSize = sizeof(*out) - sizeof(*in);
		if (out->Format.nChannels == 1)
			out->dwChannelMask = AUDIO_CHANNEL_OUT_MONO;
		else if (out->Format.nChannels == 2)
			out->dwChannelMask = AUDIO_CHANNEL_OUT_STEREO;
		else
			ALOGE("Unhandled PCM channel count: %d\n", out->Format.nChannels);
		out->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
	}
	else if (in->wFormatTag == WAVE_FORMAT_IEEE_FLOAT)
	{
		out->Format = *in;
		out->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		out->Format.cbSize = sizeof(*out) - sizeof(*in);
		if (out->Format.nChannels == 1)
			out->dwChannelMask = AUDIO_CHANNEL_OUT_MONO;
		else if (out->Format.nChannels == 2)
			out->dwChannelMask = AUDIO_CHANNEL_OUT_STEREO;
		else
			ALOGE("Unhandled IEEE float channel count: %d\n", out->Format.nChannels);
		out->SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
	}
	else
	{
		ALOGE("Unhandled format tag: 0x%04x\n", in->wFormatTag);
		return false;
	}
	return true;
}

class AudioSinkWasapi : public RefBase
{
public:
	AudioSinkWasapi(audio_config_t* pconfig) :
		UpdateSize(4096),
		NumUpdates(3),
		devid(NULL),
		mmdev(NULL),
		client(NULL),
		render(NULL),
		NotifyEvent(NULL)
	{
		memset(&config, 0x00, sizeof(config));

		this->NotifyEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	}

	~AudioSinkWasapi()
	{
		if (this->NotifyEvent)
			CloseHandle(this->NotifyEvent);
		this->NotifyEvent = NULL;

		free(this->devid);
		this->devid = NULL;
	}

	HRESULT openProxy()
	{
		void* ptr;
		HRESULT hr;

		hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_INPROC_SERVER, IID_IMMDeviceEnumerator, &ptr);
		if (SUCCEEDED(hr)) {
			IMMDeviceEnumerator* Enumerator = static_cast<IMMDeviceEnumerator*>(ptr);
			if (!this->devid)
				hr = Enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &this->mmdev);
			else
				hr = Enumerator->GetDevice(this->devid, &this->mmdev);
			Enumerator->Release();
			Enumerator = NULL;
		}

		if (SUCCEEDED(hr))
			hr = this->mmdev->Activate(IID_IAudioClient, CLSCTX_INPROC_SERVER, NULL, &ptr);
		if (SUCCEEDED(hr))
		{
			this->client = static_cast<IAudioClient*>(ptr);
		}

		if (FAILED(hr))
		{
			if (this->mmdev)
				this->mmdev->Release();
			this->mmdev = NULL;
		}

		return hr;
	}

	 void closeProxy()
	{
		if (this->client)
			this->client->Release();
		this->client = NULL;

		if (this->mmdev)
			this->mmdev->Release();
		this->mmdev = NULL;
	}


	HRESULT resetProxy(audio_config_t* pconfig)
	{
		if (!pconfig)
			return E_POINTER;

		if (!this->NotifyEvent)
			return E_POINTER;

		this->config = *pconfig;

		void* ptr = NULL;
		HRESULT hr;

		if (this->client) {
			this->client->Release();
			this->client = NULL;
		}

		hr = this->mmdev->Activate(IID_IAudioClient, CLSCTX_INPROC_SERVER, NULL, &ptr);
		if (FAILED(hr)) {
			return hr;
		}
		this->client = static_cast<IAudioClient*>(ptr);

		WAVEFORMATEXTENSIBLE OutputType = {0};
		OutputType.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;

		OutputType.dwChannelMask = config.channel_mask;
		switch (config.channel_mask) {
		case AUDIO_CHANNEL_OUT_MONO:
			OutputType.Format.nChannels = 1;
			break;
		case AUDIO_CHANNEL_OUT_STEREO:
			OutputType.Format.nChannels = 2;
			break;
		case AUDIO_CHANNEL_OUT_2POINT1:
			OutputType.Format.nChannels = 3;
			break;
		case AUDIO_CHANNEL_OUT_2POINT0POINT2:
		case AUDIO_CHANNEL_OUT_QUAD:
		case AUDIO_CHANNEL_OUT_QUAD_SIDE:
		case AUDIO_CHANNEL_OUT_SURROUND:
			OutputType.Format.nChannels = 4;
			break;
		case AUDIO_CHANNEL_OUT_PENTA:
		case AUDIO_CHANNEL_OUT_2POINT1POINT2:
		case AUDIO_CHANNEL_OUT_3POINT0POINT2:
			OutputType.Format.nChannels = 5;
			break;
		case AUDIO_CHANNEL_OUT_3POINT1POINT2:
		case AUDIO_CHANNEL_OUT_5POINT1_SIDE:
		case AUDIO_CHANNEL_OUT_5POINT1_BACK:
			OutputType.Format.nChannels = 6;
			break;
		case AUDIO_CHANNEL_OUT_5POINT1POINT2:
		case AUDIO_CHANNEL_OUT_6POINT1:
			OutputType.Format.nChannels = 7;
			break;
		case AUDIO_CHANNEL_OUT_7POINT1:
			OutputType.Format.nChannels = 8;
			break;
		case AUDIO_CHANNEL_OUT_5POINT1POINT4:
			OutputType.Format.nChannels = 9;
			break;
		case AUDIO_CHANNEL_OUT_7POINT1POINT2:
			OutputType.Format.nChannels = 10;
			break;
		case AUDIO_CHANNEL_OUT_7POINT1POINT4:
			OutputType.Format.nChannels = 12;
			break;
		default:
			return E_FAIL;
		}
		switch (config.format)
		{
		case AUDIO_FORMAT_PCM_8_BIT:
			OutputType.Format.wBitsPerSample = 8;
			OutputType.Samples.wValidBitsPerSample = 8;
			OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
			break;
		case AUDIO_FORMAT_PCM_24_BIT_PACKED:
			OutputType.Format.wBitsPerSample = 24;
			OutputType.Samples.wValidBitsPerSample = 24;
			OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
			break;
		case AUDIO_FORMAT_PCM_32_BIT:
			OutputType.Format.wBitsPerSample = 32;
			OutputType.Samples.wValidBitsPerSample = 32;
			OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
			break;
		case AUDIO_FORMAT_PCM_FLOAT:
			OutputType.Format.wBitsPerSample = 32;
			OutputType.Samples.wValidBitsPerSample = 32;
			OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
			break;
		case AUDIO_FORMAT_PCM_16_BIT:
		default:
			OutputType.Format.wBitsPerSample = 16;
			OutputType.Samples.wValidBitsPerSample = 16;
			OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
			break;
		}
		OutputType.Format.nSamplesPerSec = config.sample_rate;
		OutputType.Format.nBlockAlign = OutputType.Format.nChannels *
			OutputType.Format.wBitsPerSample / 8;
		OutputType.Format.nAvgBytesPerSec = OutputType.Format.nSamplesPerSec *
			OutputType.Format.nBlockAlign;
		OutputType.Format.cbSize = sizeof(OutputType) - sizeof(OutputType.Format);

		WAVEFORMATEX* wfx = NULL;
		hr = this->client->IsFormatSupported(AUDCLNT_SHAREMODE_SHARED, &OutputType.Format, &wfx);
		if (FAILED(hr))
		{
			//hr = this->client->GetMixFormat(&wfx);
		}
		if (FAILED(hr))
		{
			return hr;
		}

		if (wfx != NULL)
		{
			if (!MakeExtensible(&OutputType, wfx))
			{
				CoTaskMemFree(wfx);
				return E_FAIL;
			}
			CoTaskMemFree(wfx);
			wfx = NULL;

			config.sample_rate = OutputType.Format.nSamplesPerSec;
			config.channel_mask = OutputType.dwChannelMask;

			if (IsEqualGUID(OutputType.SubFormat, KSDATAFORMAT_SUBTYPE_PCM))
			{
				if (OutputType.Format.wBitsPerSample == 8)
					config.format = AUDIO_FORMAT_PCM_8_BIT;
				else if (OutputType.Format.wBitsPerSample == 16)
					config.format = AUDIO_FORMAT_PCM_16_BIT;
				else if (OutputType.Format.wBitsPerSample == 24)
					config.format = AUDIO_FORMAT_PCM_24_BIT_PACKED;
				else if (OutputType.Format.wBitsPerSample == 32)
					config.format = AUDIO_FORMAT_PCM_32_BIT;
				else
				{
					config.format = AUDIO_FORMAT_PCM_16_BIT;
					OutputType.Format.wBitsPerSample = 16;
				}
			}
			else if (IsEqualGUID(OutputType.SubFormat, KSDATAFORMAT_SUBTYPE_IEEE_FLOAT))
			{
				config.format = AUDIO_FORMAT_PCM_FLOAT;
				OutputType.Format.wBitsPerSample = 32;
			}
			else
			{
				ALOGE("Unhandled format sub-type\n");
				config.format = AUDIO_FORMAT_PCM_16_BIT;
				OutputType.Format.wBitsPerSample = 16;
				OutputType.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
			}
			OutputType.Samples.wValidBitsPerSample = OutputType.Format.wBitsPerSample;
		}

		this->format = OutputType;

		REFERENCE_TIME buf_time = ScaleCeil(this->UpdateSize * this->NumUpdates, REFTIME_PER_SEC,
			config.sample_rate);

		hr = this->client->Initialize(AUDCLNT_SHAREMODE_SHARED,
			AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
			buf_time, 0, &OutputType.Format, NULL);
		if (FAILED(hr))
		{
			ALOGE("Failed to initialize audio client: 0x%08lx\n", hr);
			return hr;
		}
			
		UINT32 buffer_len, min_len;
		REFERENCE_TIME min_per;
		hr = this->client->GetDevicePeriod(&min_per, NULL);
		if (SUCCEEDED(hr))
		{
			min_len = (UINT32)ScaleCeil(min_per, config.sample_rate, REFTIME_PER_SEC);
			/* Find the nearest multiple of the period size to the update size */
			if (min_len < this->UpdateSize)
				min_len *= (this->UpdateSize + min_len / 2) / min_len;
			hr = this->client->GetBufferSize(&buffer_len);
		}
		if (FAILED(hr))
		{
			ALOGE("Failed to get audio buffer info: 0x%08lx\n", hr);
			return hr;
		}

		this->UpdateSize = min_len;
		this->NumUpdates = buffer_len / this->UpdateSize;
		if (this->NumUpdates <= 1)
		{
			ALOGE("Audio client returned buffer_len < period*2; expect break up\n");
			this->NumUpdates = 2;
			this->UpdateSize = buffer_len / this->NumUpdates;
		}

		hr = this->client->SetEventHandle(this->NotifyEvent);
		if (FAILED(hr))
		{
			ALOGE("Failed to set event handle: 0x%08lx\n", hr);
			return hr;
		}

		return hr;
	} // resetProxy

	HRESULT startProxy()
	{
		HRESULT hr;
		void* ptr;

		ResetEvent(this->NotifyEvent);

		hr = this->client->Start();
		if (FAILED(hr))
			ALOGE("Failed to start audio client: 0x%08lx\n", hr);

		if (SUCCEEDED(hr))
			hr = this->client->GetService(IID_IAudioRenderClient, &ptr);
		if (SUCCEEDED(hr))
		{
			this->render = static_cast<IAudioRenderClient*>(ptr);
		}

		return hr;
	}

	void stopProxy()
	{
		if (!this->render)
			return;

		this->render->Release();
		this->render = NULL;
		this->client->Stop();
	}

	ssize_t writeProxy(char* data, size_t size)
	{
		if (!data || !size)
			return 0;

		UINT32  written, update_size, len;
		BYTE*   buffer;
		HRESULT hr;

		size_t data_size = size;
		UINT32 block_align = this->format.Format.nBlockAlign;
		UINT32 buffer_len  = this->UpdateSize * this->NumUpdates;

		while (size > 0) {
			hr = this->client->GetCurrentPadding(&written);
			if (FAILED(hr)) {
				ALOGE("Failed to get padding: 0x%08lx\n", hr);
				break;
			}

			if (size < block_align) {
				break;
			}

			len = min(size/block_align, buffer_len - written);
			update_size = len * block_align;

			hr = this->render->GetBuffer(len, &buffer);
			if (SUCCEEDED(hr)) {
				memcpy(buffer, data, update_size);
				data += update_size;
				size -= update_size;

				hr = this->render->ReleaseBuffer(len, 0);
			}
			if (FAILED(hr)) {
				ALOGE("Failed to buffer data: 0x%08lx\n", hr);
				break;
			}
		}

		return (data_size - size);
	}

	const audio_config_t& getConfig() const { return config; };
	const unsigned int getBufferSize() const { return (UpdateSize * NumUpdates); };
	const unsigned int getLatency() const { return 0; };

private:
	audio_config_t        config;
	WAVEFORMATEXTENSIBLE  format;

	unsigned int UpdateSize;
	unsigned int NumUpdates;
	unsigned int DataAlign;

	WCHAR* devid;
	IMMDevice* mmdev;
	IAudioClient* client;
	IAudioRenderClient* render;
	HANDLE NotifyEvent;
};

struct stub_audio_device {
	struct audio_hw_device device;
};

struct stub_stream_out {
	struct audio_stream_out stream;
	sp<AudioSinkWasapi>     sink;
};

struct stub_stream_in {
	struct audio_stream_in stream;
};

static uint32_t out_get_sample_rate(const struct audio_stream* stream)
{
	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if ((out) && (out->sink != NULL)) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sink->getConfig().sample_rate);
		return (out->sink->getConfig().sample_rate);
	}
	else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return (44100);
	}
}

static int out_set_sample_rate(struct audio_stream* stream, uint32_t rate)
{
	ALOGV("[0x%X]out_set_sample_rate: %d", stream, rate);

	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if ((out) && (out->sink != NULL)) {
		audio_config_t config = out->sink->getConfig();
		config.sample_rate = rate;
		out->sink->resetProxy(&config);

		return (0);
	}
	else {
		return -ENOSYS;
	}
}

static size_t out_get_buffer_size(const struct audio_stream* stream)
{
	struct stub_stream_out* out = (struct stub_stream_out*)stream;
	
	if ((out) && (out->sink != NULL)) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sink->getBufferSize());
		return (out->sink->getBufferSize());
	}
	else
	{
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return 4096;
	}
}

static audio_channel_mask_t out_get_channels(const struct audio_stream* stream)
{
	struct stub_stream_out* out = (struct stub_stream_out*)stream;
	
	if ((out) && (out->sink != NULL)) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sink->getConfig().channel_mask);
		return (out->sink->getConfig().channel_mask);
	} 
	else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return AUDIO_CHANNEL_OUT_STEREO;
	}
}

static audio_format_t out_get_format(const struct audio_stream* stream)
{
	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if ((out) && (out->sink != NULL)) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sink->getConfig().format);
		return (out->sink->getConfig().format);
	} 
	else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return AUDIO_FORMAT_PCM_16_BIT;
	}
}

static int out_set_format(struct audio_stream* stream, audio_format_t format)
{
	ALOGV("[0x%X]%s: 0x%X", stream, __FUNCTION__, format);

	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if ((out) && (out->sink != NULL)) {
		audio_config_t config = out->sink->getConfig();
		config.format = format;
		out->sink->resetProxy(&config);

		return (0);
	}
	else {
		return -ENOSYS;
	}
}

static int out_standby(struct audio_stream* stream)
{
	ALOGV("[0x%X]%s", stream, __FUNCTION__);

	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	return 0;
}

static int out_dump(const struct audio_stream* stream, int fd)
{
	ALOGV("[0x%X]%s: %d", stream, __FUNCTION__, fd);
	return 0;
}

static int out_set_parameters(struct audio_stream* stream, const char* kvpairs)
{
	ALOGV("[0x%X]%s: %s", stream, __FUNCTION__, kvpairs);
	return 0;
}

static char* out_get_parameters(const struct audio_stream* stream, const char* keys)
{
	ALOGV("[0x%X]%s", stream, __FUNCTION__);
	return _strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out* stream)
{
	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if ((out) && (out->sink != NULL)) {
		ALOGV("[0x%X]%s :%d", out, __FUNCTION__, out->sink->getLatency());
		return (out->sink->getLatency());
	}
	else {
		ALOGV("%s INVALID STREAM !!!", __FUNCTION__);
		return 0;
	}
}

static int out_set_volume(struct audio_stream_out* stream, float left,
	float right)
{
	ALOGV("[0x%X]%s: Left:%f Right:%f", stream, __FUNCTION__, left, right);
	return 0;
}

static ssize_t out_write(struct audio_stream_out* stream, const void* buffer,
	size_t bytes)
{
	ALOGV("[0x%X]%s: bytes: 0x%X, %d", stream, __FUNCTION__, buffer, bytes);

	if (buffer == NULL || bytes <= 0) {
		ALOGV("%s invalid input data !", __FUNCTION__);
		return bytes;
	}

	struct stub_stream_out* out = (struct stub_stream_out*)stream;
	if (out == NULL || out->sink == NULL) {
		ALOGV("%s no output sink !", __FUNCTION__);
		return -1;
	}

	return (out->sink->writeProxy((char*)(buffer), bytes));
}

static int out_get_render_position(const struct audio_stream_out* stream,
	uint32_t* dsp_frames)
{
	*dsp_frames = 0;
	ALOGV("[0x%X]%s: dsp_frames: %p", stream, __FUNCTION__, dsp_frames);
	return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream* stream, effect_handle_t effect)
{
	ALOGV("[0x%X]%s: %p", stream, __FUNCTION__, effect);
	return 0;
}

static int out_remove_audio_effect(const struct audio_stream* stream, effect_handle_t effect)
{
	ALOGV("[0x%X]out_remove_audio_effect: %p", stream, effect);
	return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out* stream,
	int64_t* timestamp)
{
	*timestamp = 0;
	ALOGV("[0x%X]%s: %ld", stream, __FUNCTION__, (long int)(*timestamp));
	return -EINVAL;
}

/** audio_stream_in implementation **/
static uint32_t in_get_sample_rate(const struct audio_stream* stream)
{
	ALOGV("in_get_sample_rate");
	return 8000;
}

static int in_set_sample_rate(struct audio_stream* stream, uint32_t rate)
{
	ALOGV("in_set_sample_rate: %d", rate);
	return -ENOSYS;
}

static size_t in_get_buffer_size(const struct audio_stream* stream)
{
	ALOGV("in_get_buffer_size: %d", 320);
	return 320;
}

static audio_channel_mask_t in_get_channels(const struct audio_stream* stream)
{
	ALOGV("in_get_channels: %d", AUDIO_CHANNEL_IN_MONO);
	return AUDIO_CHANNEL_IN_MONO;
}

static audio_format_t in_get_format(const struct audio_stream* stream)
{
	return AUDIO_FORMAT_PCM_16_BIT;
}

static int in_set_format(struct audio_stream* stream, audio_format_t format)
{
	return -ENOSYS;
}

static int in_standby(struct audio_stream* stream)
{
	struct stub_stream_in* in = (struct stub_stream_in*)stream;

	return 0;
}

static int in_dump(const struct audio_stream* stream, int fd)
{
	return 0;
}

static int in_set_parameters(struct audio_stream* stream, const char* kvpairs)
{
	return 0;
}

static char* in_get_parameters(const struct audio_stream* stream,
	const char* keys)
{
	return _strdup("");
}

static int in_set_gain(struct audio_stream_in* stream, float gain)
{
	return 0;
}

static ssize_t in_read(struct audio_stream_in* stream, void* buffer,
	size_t bytes)
{
	ALOGV("in_read: bytes %d", bytes);

	return bytes;
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in* stream)
{
	return 0;
}

static int in_add_audio_effect(const struct audio_stream* stream, effect_handle_t effect)
{
	return 0;
}

static int in_remove_audio_effect(const struct audio_stream* stream, effect_handle_t effect)
{
	return 0;
}

static int adev_open_output_stream(struct audio_hw_device* dev,
	audio_io_handle_t handle,
	audio_devices_t devices,
	audio_output_flags_t flags,
	struct audio_config* config,
	struct audio_stream_out** stream_out,
	const char* address)
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
	struct stub_audio_device* ladev = (struct stub_audio_device*)dev;
	struct stub_stream_out* out = (struct stub_stream_out*)calloc(1, sizeof(struct stub_stream_out));
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


	out->sink = new AudioSinkWasapi(NULL);
	if (out->sink != NULL) {
		out->sink->openProxy();
		out->sink->resetProxy(config);
		out->sink->startProxy();
	}
	else {
		goto err_open;
	}

	*stream_out = &out->stream;

	return 0;

err_open:
	free(out);
	*stream_out = NULL;
	return ret;
}

static void adev_close_output_stream(struct audio_hw_device* dev,
	struct audio_stream_out* stream)
{
	ALOGV("adev_close_output_stream...");

	struct stub_audio_device* ladev = (struct stub_audio_device*)dev;
	struct stub_stream_out* out = (struct stub_stream_out*)stream;

	if (out->sink != NULL) {
		out->sink->stopProxy();
		out->sink->closeProxy();
		out->sink.clear();
		out->sink = NULL;
	}

	free(out);
}

static int adev_set_parameters(struct audio_hw_device* dev, const char* kvpairs)
{
	ALOGV("adev_set_parameters");
	return -ENOSYS;
}

static char* adev_get_parameters(const struct audio_hw_device* dev,
	const char* keys)
{
	ALOGV("adev_get_parameters");
	return _strdup("");
}

static int adev_init_check(const struct audio_hw_device* dev)
{
	ALOGV("adev_init_check");
	return 0;
}

static int adev_set_voice_volume(struct audio_hw_device* dev, float volume)
{
	ALOGV("adev_set_voice_volume: %f", volume);
	return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device* dev, audio_mode_t mode)
{
	ALOGV("adev_set_mode: %d", mode);
	return 0;
}

static int adev_set_mic_mute(struct audio_hw_device* dev, bool state)
{
	ALOGV("adev_set_mic_mute: %d", state);
	return -ENOSYS;
}

static int adev_get_mic_mute(const struct audio_hw_device* dev, bool* state)
{
	ALOGV("adev_get_mic_mute");
	return -ENOSYS;
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device* dev,
	const struct audio_config* config)
{
	ALOGV("adev_get_input_buffer_size: %d", 320);
	return 320;
}

static int adev_open_input_stream(struct audio_hw_device* dev,
	audio_io_handle_t handle,
	audio_devices_t devices,
	struct audio_config* config,
	struct audio_stream_in** stream_in,
	audio_input_flags_t flags,
	const char* address,
	audio_source_t source)
{
	ALOGV("adev_open_input_stream dev      :0x%X", dev);
	ALOGV("adev_open_input_stream handle   :%d", handle);
	ALOGV("adev_open_input_stream devices  :%d", devices);
	if (config) {
		ALOGV("adev_open_input_stream config->sample_rate :%d", config->sample_rate);
		ALOGV("adev_open_input_stream config->channel_mask:0x%X", config->channel_mask);
		ALOGV("adev_open_input_stream config->format      :0x%X", config->format);
		ALOGV("adev_open_input_stream config->frame_count :%d", config->frame_count);
	}
	ALOGV("adev_open_input_stream stream_in:0x%X", stream_in);
	ALOGV("adev_open_input_stream flags    :0x%X", flags);
	if (address) {
		ALOGV("adev_open_input_stream address :%s", address);
	}
	ALOGV("adev_open_input_stream source   :%d", source);


	struct stub_audio_device* ladev = (struct stub_audio_device*)dev;
	struct stub_stream_in* in;
	int ret;

	in = (struct stub_stream_in*)calloc(1, sizeof(struct stub_stream_in));
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

static void adev_close_input_stream(struct audio_hw_device* dev,
	struct audio_stream_in* stream)
{
	ALOGV("adev_close_input_stream...");

	struct stub_stream_in* in = (struct stub_stream_in*)stream;

	free(in);

	return;
}

static int adev_dump(const audio_hw_device_t* device, int fd)
{
	ALOGV("adev_dump");

	return 0;
}

static int adev_close(hw_device_t* device)
{
	ALOGV("adev_close");

	return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
	hw_device_t** device)
{
	ALOGV("adev_open: %s", name);

	struct stub_audio_device* adev;

	if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
		return -EINVAL;

	adev = (struct stub_audio_device*)calloc(1, sizeof(struct stub_audio_device));
	if (!adev)
		return -ENOMEM;

	adev->device.common.tag = HARDWARE_DEVICE_TAG;
	adev->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
	adev->device.common.module = (struct hw_module_t*)module;
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
