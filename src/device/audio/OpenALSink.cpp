
//#define LOG_NDEBUG 0
#define LOG_TAG "OpenALSink"
#include "utils/ADebugExt.h"
#include "utils/Log.h"
#include "utils/Errors.h"
#include "OpenALSink.h"

namespace android {

// The number of buffers and bytes-per-buffer for our stream are set here. The number of buffers should be two or more, and the buffer size should be a multiple of the frame size (by default, OpenAL's largest frame size is 4, however extensions that can add more formats may be larger). Slower // // // systems may need more buffers/larger buffer sizes.

#define BUFFER_MS (100)

/******************************************************************************
    OpenALSink
******************************************************************************/

OpenALSink::OpenALSink() :
    mDev(NULL),
    mCtx(NULL)
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

    return 0;
}

ssize_t     
OpenALSink::frameCount() const
{
    return 0;
}

ssize_t     
OpenALSink::channelCount() const
{
    return 0;
}

ssize_t     
OpenALSink::frameSize() const
{
    return 0;
}

uint32_t    
OpenALSink::latency() const
{
    return 0;
}

float       
OpenALSink::msecsPerFrame() const
{
    return 0;
}

status_t    
OpenALSink::getPosition(uint32_t *position) const
{
    AUTO_LOG();

    CHECK_PTR_EXT(position, BAD_VALUE)

    (*position) = mAud.pos;

    RETURN(OK);
}

status_t    
OpenALSink::getTimestamp(AudioTimestamp &ts) const
{
    return 0;
}

int64_t     
OpenALSink::getPlayedOutDurationUs(int64_t nowUs) const
{
    return 0;
}

status_t    
OpenALSink::getFramesWritten(uint32_t *frameswritten) const
{
    return 0;
}

audio_session_t 
OpenALSink::getSessionId() const
{
    return AUDIO_SESSION_NONE;
}

audio_stream_type_t 
OpenALSink::getAudioStreamType() const
{
    return AUDIO_STREAM_DEFAULT;
}

uint32_t    
OpenALSink::getSampleRate() const
{
    return 0;
}

int64_t     
OpenALSink::getBufferDurationInUs() const
{
    return 0;
}

status_t 
OpenALSink::createSink_l()
{
    AUTO_LOG();

    // First the standard open-device, create-context, set-context..
    mDev = alcOpenDevice(NULL);
    CHECK_PTR_EXT(mDev, NO_MEMORY);

    mCtx = alcCreateContext(mDev, NULL);
    CHECK_PTR_EXT(mCtx, NO_MEMORY);

    alcMakeContextCurrent(mCtx);

    // Generate the buffers and sources
    alGenBuffers(BUFFER_COUNT, mAud.buf);
    alGenSources(1, &(mAud.src));
    CHECK_IS_EXT((AL_NO_ERROR == alGetError()), BAD_VALUE);
    
    // Get the sample frequency (32-bit little-endian)
    mAud.frq = AudioSinkBase::mSampleRate;

    // Now convert the given channel count and bit depth into an OpenAL format.
    status_t ret = convertFormatType();
    CHECK_IS_EXT((OK == ret), ret);

    // Calculate buffer size
    mAud.size = (BUFFER_MS/BUFFER_COUNT) * mAud.bits * mChannelCount * (mAud.frq/1000);

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
    AUTO_LOG();

    /* Get relevant source info */
    ALint state = 0;
    alGetSourcei(mAud.src, AL_SOURCE_STATE, &state);

    return 0;
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
		alDeleteBuffers(BUFFER_COUNT, mAud.buf);
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
