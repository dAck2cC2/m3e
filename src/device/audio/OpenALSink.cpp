
//#define LOG_NDEBUG 0
#define LOG_TAG "OpenALSink"
#include <utils/Log.h>
#include <OpenALSink.h>

namespace android {

/******************************************************************************
    OpenALSink
******************************************************************************/

OpenALSink::OpenALSink()
{

}

OpenALSink::~OpenALSink()
{

}

bool        
OpenALSink::ready() const
{
    return false;
}

ssize_t     
OpenALSink::bufferSize() const
{
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
    return 0;
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
OpenALSink::open(
    uint32_t sampleRate, int channelCount, audio_channel_mask_t channelMask,
    audio_format_t format, int bufferCount, AudioCallback cb, void *cookie,
    audio_output_flags_t flags, const audio_offload_info_t *offloadInfo,
    bool doNotReconnect, uint32_t suggestedFrameCount
)
{
    return 0;
}

status_t    
OpenALSink::start()
{
    return 0;
}

ssize_t     
OpenALSink::write(const void* buffer, size_t size, bool blocking)
{
    return 0;
}

void        
OpenALSink::stop()
{
    return;
}

void        
OpenALSink::flush()
{
    return;
}

void        
OpenALSink::pause()
{
    return;
}

void        
OpenALSink::close()
{
    return;
}

status_t    
OpenALSink::setPlaybackRate(const AudioPlaybackRate& rate)
{
    return 0;
}

status_t    
OpenALSink::getPlaybackRate(AudioPlaybackRate* rate /* nonnull */)
{
    return 0;
}

status_t 
OpenALSink::createSink_l()
{
    return 0;
}

status_t    
OpenALSink::restoreTrack_l(const char *from)
{
    return 0;
}

bool        
OpenALSink::isOffloaded_l() const
{
    return false;
}

uint32_t    
OpenALSink::updateAndGetPosition_l()
{
    return 0;
}

void        
OpenALSink::flush_l()
{
    return;
}

nsecs_t 
OpenALSink::processAudioBuffer_l()
{
    return 0;
}

}  // namespace android
