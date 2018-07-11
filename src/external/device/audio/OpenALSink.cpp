
//#define LOG_NDEBUG 0
#define LOG_TAG "OpenALSink"
#include "utils/ADebugExt.h"
#include "utils/Log.h"
#include "utils/Errors.h"
#include "OpenALSink.h"

namespace android {

// The number of buffers and bytes-per-buffer for our stream are set here. The number of buffers should be two or more, and the buffer size should be a multiple of the frame size (by default, OpenAL's largest frame size is 4, however extensions that can add more formats may be larger). Slower // // // systems may need more buffers/larger buffer sizes.

#define OPENAL_SINK_BUFFER_MS (100)

/******************************************************************************
    OpenALSink
******************************************************************************/

OpenALSink::OpenALSink()
{
    AUTO_LOG();

    memset(&mAud, 0x00, sizeof(mAud));
}

OpenALSink::~OpenALSink()
{
    AUTO_LOG();
}

ssize_t     
OpenALSink::bufferSize() const
{
    AUTO_LOG();

    return (mAud.size);
}

status_t    
OpenALSink::getTimestamp(AudioTimestamp &ts) const
{
    AUTO_LOG();
    
    return 0;
}

int64_t     
OpenALSink::getPlayedOutDurationUs(int64_t nowUs) const
{
    AUTO_LOG();
    
    return 0;
}

status_t    
OpenALSink::getFramesWritten(uint32_t *frameswritten) const
{
    AUTO_LOG();
    
    return 0;
}

int64_t     
OpenALSink::getBufferDurationInUs() const
{
    AUTO_LOG();
    
    return 0;
}

status_t    
OpenALSink::getPosition(uint32_t *position) const
{
    AUTO_LOG();

    AutoMutex lock(AudioSinkBase::mLock);

    CHECK_PTR_EXT(position, BAD_VALUE);    

    (*position) = mAud.pos;

    RETURN(OK);
}

status_t 
OpenALSink::createSink_l()
{
    AUTO_LOG();

    // First the standard open-device, create-context, set-context..
    ALCdevice* dev = alcOpenDevice(NULL);
    CHECK_PTR_EXT(dev, NO_MEMORY);

    ALCcontext* ctx = alcCreateContext(dev, NULL);
    CHECK_PTR_EXT(ctx, NO_MEMORY);

    alcMakeContextCurrent(ctx);

    // Generate the buffers and sources
    alGenBuffers(OPENAL_SINK_BUFFER_COUNT, mAud.buf);
    alGenSources(1, &(mAud.src));
    CHECK_IS_EXT((AL_NO_ERROR == alGetError()), BAD_VALUE);
    
    // Get the sample frequency (32-bit little-endian)
    mAud.frq = AudioSinkBase::mSampleRate;

    // Now convert the given channel count and bit depth into an OpenAL format.
    status_t ret = convertFormatType();
    CHECK_IS_EXT((OK == ret), ret);

    // Calculate buffer size
    if (AudioSinkBase::mFrameCount <= 0) {
        AudioSinkBase::mFrameCount = (mAud.frq * OPENAL_SINK_BUFFER_MS) / 1000;
        if (AudioSinkBase::mFrameCount == 0) {
            AudioSinkBase::mFrameCount = 1024;
        }
        AudioSinkBase::mLatency = (1000*AudioSinkBase::mFrameCount) / mAud.frq; 
    }
    mAud.size = AudioSinkBase::mFrameSize * AudioSinkBase::mFrameCount;

    ALOGD("create frameCount: %d", AudioSinkBase::mFrameCount);
    ALOGD("create latency: %d", AudioSinkBase::mLatency);
    ALOGD("create format: %d", mAud.fmt);
    ALOGD("create frequency: %d", mAud.frq);
    ALOGD("create bitsPerSample: %d", mAud.bits);
    ALOGD("create bufferSize: %d", mAud.size);

    RETURN(OK);
}

status_t    
OpenALSink::restoreTrack_l(const char *from)
{
    AUTO_LOG();

    return 0;
}

bool        
OpenALSink::isOffloaded_l() const
{
    AUTO_LOG();

    return false;
}

uint32_t    
OpenALSink::updateAndGetPosition_l()
{
    AUTO_LOG();

    return mAud.pos;
}

nsecs_t 
OpenALSink::processAudioBuffer_l()
{
    //AUTO_LOG();

    CHECK_PTR_EXT(AudioSinkBase::mCblk, NS_NEVER);
    CHECK_IS_EXT((mAud.size > 0), NS_NEVER);

	static struct {
        ALint  cnt;
		ALuint buf[OPENAL_SINK_BUFFER_COUNT];
	} s_free = { 0 };

    /* Get relevant source info */
    ALint state = 0;
    alGetSourcei(mAud.src, AL_SOURCE_STATE, &state);
    if (AL_INITIAL == state) {
        for (int i = 0; i < OPENAL_SINK_BUFFER_COUNT; ++i) {
            s_free.buf[i] = mAud.buf[i];
        }
        s_free.cnt = OPENAL_SINK_BUFFER_COUNT;
    } else {
        while (s_free.cnt <= 0) {
            alGetSourcei(mAud.src, AL_BUFFERS_PROCESSED, &s_free.cnt);
            alSourceUnqueueBuffers(mAud.src, s_free.cnt, s_free.buf);
            CHECK_IS_EXT((AL_NO_ERROR == alGetError()), NS_WHENEVER);

            if (0 == s_free.cnt) {
                //ALOGV("wait for playback ...");
                usleep(100);
            }
        }
    }

    CHECK_IS_EXT((s_free.cnt > 0), NS_WHENEVER);

    void* buf = malloc(mAud.size);
    CHECK_PTR_EXT(buf, NS_INACTIVE);

    size_t nsrc = AudioSinkBase::mCblk(this, buf, mAud.size, AudioSinkBase::mCookie, CB_EVENT_FILL_BUFFER);
    if ((nsrc <= 0) || (nsrc > mAud.size)) {
        free(buf);
        RETURN(NS_WHENEVER);
    }    

	alBufferData(s_free.buf[s_free.cnt - 1], mAud.fmt, buf, nsrc, mAud.frq);
	alSourceQueueBuffers(mAud.src, 1, &s_free.buf[s_free.cnt - 1]);
	s_free.cnt--;
    free(buf);

    mAud.pos += nsrc;

    if ((state != AL_PLAYING) && (state != AL_PAUSED)) {
        ALint queued = 0;

        /* If no buffers are queued, playback is finished */
        alGetSourcei(mAud.src, AL_BUFFERS_QUEUED, &queued);
        if(queued == 0) {
            return NS_INACTIVE;
        }

        alSourcePlay(mAud.src);
        CHECK_IS_EXT((AL_NO_ERROR == alGetError()), NS_WHENEVER);
    }

    RETURN(0);
}

void        
OpenALSink::flush_l()
{
    return;
}

void
OpenALSink::close_l()
{
    AUTO_LOG();

	if (mAud.src) {
		alDeleteSources(1, &mAud.src);
		alDeleteBuffers(OPENAL_SINK_BUFFER_COUNT, mAud.buf);
		memset(&mAud, 0x00, sizeof(mAud));
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

status_t 
OpenALSink::convertFormatType()
{
    AUTO_LOG();

    // Now convert the given channel count and bit depth into an OpenAL format. 
    // We could use extensions to support more formats (eg. surround sound, 
    // floating-point samples), but that is beyond the scope of this tutorial

    if (AUDIO_FORMAT_PCM_8_BIT == mFormat) {
        mAud.bits = 8;
		if (1 == mChannelCount) {
			mAud.fmt = AL_FORMAT_MONO8;
		} else if (2 == mChannelCount) {
			mAud.fmt = AL_FORMAT_STEREO8;
		} else if (alIsExtensionPresent("AL_EXT_MCFORMATS")) {
			if (4 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_QUAD8");
			} else if (5 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_51CHN8");
			} else if (6 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_61CHN8");
			} else if (7 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_71CHN8");
			} else {
                RETURN(BAD_TYPE);
            }
        }
    }
    else if ((AUDIO_FORMAT_PCM_16_BIT == mFormat) || (AUDIO_FORMAT_DEFAULT == mFormat)) {
        mAud.bits = 16;
		if (1 == mChannelCount) {
			mAud.fmt = AL_FORMAT_MONO16;
		} else if (2 == mChannelCount) {
			mAud.fmt = AL_FORMAT_STEREO16;
		} else if (alIsExtensionPresent("AL_EXT_MCFORMATS")) {
			if (4 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_QUAD16");
			} else if (5 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_51CHN16");
			} else if (6 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_61CHN16");
			} else if (7 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_71CHN16");
			} else {
                RETURN(BAD_TYPE);
            }
		}         
    }
    else if (AUDIO_FORMAT_PCM_32_BIT == mFormat) {
        mAud.bits = 32;
		if (1 == mChannelCount) {
			mAud.fmt = alGetEnumValue("AL_FORMAT_MONO_FLOAT32");
		} else if (2 == mChannelCount) {
			mAud.fmt = alGetEnumValue("AL_FORMAT_STEREO_FLOAT32");
		} else if (alIsExtensionPresent("AL_EXT_MCFORMATS")) {
			if (4 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_QUAD32");
			} else if (5 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_51CHN32");
			} else if (6 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_61CHN32");
			} else if (7 == mChannelCount) {
				mAud.fmt = alGetEnumValue("AL_FORMAT_71CHN32");
			}  else {
                RETURN(BAD_TYPE);
            }
		} 
    } else {
        RETURN(BAD_TYPE);
    }

    RETURN(OK);
}

}  // namespace android
