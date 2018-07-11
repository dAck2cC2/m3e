
//#define LOG_NDEBUG 0
#define LOG_TAG "AudioBaseSink"
#include <utils/ADebugExt.h>
#include <utils/Log.h>
#include <AudioSinkBase.h>

#include <system/audio.h>

namespace android {

/******************************************************************************
    AudioSinkBase
******************************************************************************/

AudioSinkBase::AudioSinkBase() :  
    mCblk(NULL), mStatus(NO_INIT), mState(STATE_STOPPED)
{
    AUTO_LOG();
}

AudioSinkBase::~AudioSinkBase()
{
    AUTO_LOG();
    
    if (mAudioSinkThread != 0) {
        //mProxy->interrupt();
        mAudioSinkThread->requestExit();   // see comment in AudioTrack.h
        mAudioSinkThread->requestExitAndWait();
        mAudioSinkThread.clear();
    }
}

bool        
AudioSinkBase::ready() const
{
    AUTO_LOG();

    AutoMutex lock(mLock);

    return (NO_ERROR == mStatus);
}

ssize_t     
AudioSinkBase::bufferSize() const
{
    AUTO_LOG();
    
    return 0;
}

ssize_t     
AudioSinkBase::frameCount() const
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    return (mFrameCount);
}

ssize_t     
AudioSinkBase::channelCount() const
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    return (mChannelCount);
}

ssize_t     
AudioSinkBase::frameSize() const
{
    AUTO_LOG();

    AutoMutex lock(mLock);    

    return (mFrameSize);
}

uint32_t    
AudioSinkBase::latency() const
{
    AUTO_LOG();

    AutoMutex lock(mLock);

    return (mLatency);
}

float       
AudioSinkBase::msecsPerFrame() const
{
    AUTO_LOG();

    AutoMutex lock(mLock);

    if (mSampleRate > 0) { 
        return ((float)1.0f / mSampleRate);
    } else {
        return (0);
    }
}

status_t    
AudioSinkBase::getPosition(uint32_t *position) const
{
    AUTO_LOG();

    RETURN(OK);
}

status_t    
AudioSinkBase::getTimestamp(AudioTimestamp &ts) const
{
    AUTO_LOG();
        
    RETURN(OK);
}

int64_t     
AudioSinkBase::getPlayedOutDurationUs(int64_t nowUs) const
{
    AUTO_LOG();
    
    return 0;
}

status_t    
AudioSinkBase::getFramesWritten(uint32_t *frameswritten) const
{
    AUTO_LOG();
    
    return 0;
}

audio_session_t 
AudioSinkBase::getSessionId() const
{
    AUTO_LOG();
    
    return AUDIO_SESSION_NONE;
}

audio_stream_type_t 
AudioSinkBase::getAudioStreamType() const
{
    AUTO_LOG();
    
    return AUDIO_STREAM_DEFAULT;
}

uint32_t    
AudioSinkBase::getSampleRate() const
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);
    
    return (mSampleRate);
}

int64_t     
AudioSinkBase::getBufferDurationInUs() const
{
    AUTO_LOG();
        
    return 0;
}

status_t    
AudioSinkBase::open(
    uint32_t sampleRate, int channelCount, audio_channel_mask_t channelMask,
    audio_format_t format, int bufferCount, AudioCallback cbf, void *cookie,
    audio_output_flags_t flags, const audio_offload_info_t *offloadInfo,
    bool doNotReconnect, uint32_t suggestedFrameCount
)
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    ALOGD("open sampleRate : %d", sampleRate);
    ALOGD("open channelCount : %d", channelCount);
    ALOGD("open channelMask : 0x%X", channelMask);
    ALOGD("open format : 0x%X", format);
    ALOGD("open bufferCount : %d", bufferCount);
    ALOGD("open cbf : 0x%X", cbf);    
    ALOGD("open cookie : 0x%X", cookie);    
    ALOGD("open flags : 0x%X", flags);
    ALOGD("open offloadInfo : 0x%X", offloadInfo);
    ALOGD("open doNotReconnect : %d", doNotReconnect);
    ALOGD("open suggestedFrameCount : %d", suggestedFrameCount);
    
    //////////////////////////////////////////////////////
    //  format
    /////////////////////////////////////////////////////

    if (format == AUDIO_FORMAT_DEFAULT) {
        format = AUDIO_FORMAT_PCM_16_BIT;
    }
    // validate parameters
    if (!audio_is_valid_format(format)) {
        ALOGE("Invalid format %#x", format);
        RETURN(BAD_VALUE);
    }
    mFormat = format;

    //////////////////////////////////////////////////////
    //  channel mask and count
    /////////////////////////////////////////////////////

    mChannelCount = channelCount;
    // playing to an AudioTrack, set up mask if necessary
    mChannelMask = channelMask == CHANNEL_MASK_USE_CHANNEL_ORDER ?
                audio_channel_out_mask_from_count(channelCount) : channelMask;
    CHECK_IS_EXT((0 != mChannelMask), BAD_VALUE);   
    if (!audio_is_output_channel(mChannelMask)) {
        ALOGE("Invalid channel mask %#x", mChannelMask);
        RETURN(BAD_VALUE);
    }
    // check the mask and count
    int channelCountFromMask = audio_channel_count_from_out_mask(mChannelMask);
    CHECK_IS_EXT((mChannelCount == channelCountFromMask), BAD_VALUE);

    //////////////////////////////////////////////////////
    //  frame size
    /////////////////////////////////////////////////////

    if (flags & AUDIO_OUTPUT_FLAG_DIRECT) {
        if (audio_has_proportional_frames(format)) {
            mFrameSize = channelCount * audio_bytes_per_sample(format);
        } else {
            mFrameSize = sizeof(uint8_t);
        }
    } else {
        ALOG_ASSERT(audio_has_proportional_frames(format));
        mFrameSize = channelCount * audio_bytes_per_sample(format);
        // createTrack will return an error if PCM format is not supported by server,
        // so no need to check for specific PCM formats here
    }

    //////////////////////////////////////////////////////
    //  sample rate
    /////////////////////////////////////////////////////

    // sampling rate must be specified for direct outputs
    if (sampleRate == 0 && (flags & AUDIO_OUTPUT_FLAG_DIRECT) != 0) {
        RETURN(BAD_VALUE);
    }
    mSampleRate = sampleRate;

    //////////////////////////////////////////////////////
    //  offload
    /////////////////////////////////////////////////////

    // Make copy of input parameter offloadInfo so that in the future:
    //  (a) createTrack_l doesn't need it as an input parameter
    //  (b) we can support re-creation of offloaded tracks
    if (offloadInfo != NULL) {
        mOffloadInfoCopy = *offloadInfo;
        mOffloadInfo = &mOffloadInfoCopy;
    } else {
        mOffloadInfo = NULL;
    }

    //////////////////////////////////////////////////////
    //  Frame Count and latency
    /////////////////////////////////////////////////////

    mSuggestedFrameCount = suggestedFrameCount;

    // They should be modified by createSink_l()
    mFrameCount = suggestedFrameCount;
    mLatency = (1000*mFrameCount) / mSampleRate;

    //////////////////////////////////////////////////////
    //  others
    /////////////////////////////////////////////////////

    mBufferCount = bufferCount;
    mFlags = flags;
    mDoNotReconnect = doNotReconnect;

    //////////////////////////////////////////////////////
    //  callback and thread
    /////////////////////////////////////////////////////

    mCookie = cookie;
    mCblk = cbf;
    if (cbf != NULL) {
        mAudioSinkThread = new AudioSinkThread(*this, false);
        mAudioSinkThread->run("AudioTrack", ANDROID_PRIORITY_AUDIO, 0 /*stack*/);
        // thread begins in paused state, and will not reference us until start()
    }

    //////////////////////////////////////////////////////
    //  initialize sink
    /////////////////////////////////////////////////////

    status_t status = createSink_l();

    if (status != NO_ERROR) {
        if (mAudioSinkThread != 0) {
            mAudioSinkThread->requestExit();   // see comment in AudioTrack.h
            mAudioSinkThread->requestExitAndWait();
            mAudioSinkThread.clear();
        }
        RETURN(status);
    }

    mStatus = NO_ERROR;

    RETURN(NO_ERROR);
}

status_t    
AudioSinkBase::start()
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    if (mState == STATE_ACTIVE) {
        return INVALID_OPERATION;
    }
    State previousState = mState;
    if (previousState == STATE_PAUSED_STOPPING) {
        mState = STATE_STOPPING;
    } else {
        mState = STATE_ACTIVE;
    }

    (void) updateAndGetPosition_l();

    status_t status = restoreTrack_l("start");

    // resume or pause the callback thread as needed.
    sp<AudioSinkThread> t = mAudioSinkThread;
    if (status == NO_ERROR) {
        if (t != 0) {
            if (previousState == STATE_STOPPING) {
                //mProxy->interrupt();
            } else {
                t->resume();
            }
        }
    } else {
        ALOGE("start() status %d", status);
        mState = previousState;
        if (t != 0) {
            if (previousState != STATE_STOPPING) {
                t->pause();
            }
        }
    }
    
    RETURN(status);
}

ssize_t     
AudioSinkBase::write(const void* buffer, size_t size, bool blocking)
{
    AUTO_LOG();
    
    return 0;
}

void        
AudioSinkBase::stop()
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    if (mState != STATE_ACTIVE && mState != STATE_PAUSED) {
        return;
    }

    if (isOffloaded_l()) {
        mState = STATE_STOPPING;
    } else {
        mState = STATE_STOPPED;
        //mReleased = 0;
    }

    sp<AudioSinkThread> t = mAudioSinkThread;
    if (t != 0) {
        if (!isOffloaded_l()) {
            t->pause();
        }
    } 

    return;
}

void        
AudioSinkBase::flush()
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);
    
    if (mState == STATE_ACTIVE || mState == STATE_FLUSHED) {
        return;
    }
    
    return (flush_l());
}

void        
AudioSinkBase::pause()
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);
    
    if (mState == STATE_ACTIVE) {
        mState = STATE_PAUSED;
    } else if (mState == STATE_STOPPING) {
        mState = STATE_PAUSED_STOPPING;
    } else {
        return;
    }
    
    return;
}

void        
AudioSinkBase::close()
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);

    return (close_l());
}

status_t    
AudioSinkBase::setPlaybackRate(const AudioPlaybackRate& rate)
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);
    
    return 0;
}

status_t    
AudioSinkBase::getPlaybackRate(AudioPlaybackRate* rate /* nonnull */)
{
    AUTO_LOG();
    
    AutoMutex lock(mLock);
    
    return 0;
}

/******************************************************************************
    AudioSinkThread
******************************************************************************/

AudioSinkBase::AudioSinkThread::AudioSinkThread(AudioSinkBase& receiver, bool bCanCallJava)
   : Thread(bCanCallJava), mReceiver(receiver), mPaused(true), mPausedInt(false), mPausedNs(0LL),
     mIgnoreNextPausedInt(false)
{
    AUTO_LOG();
}

AudioSinkBase::AudioSinkThread::~AudioSinkThread()
{
    AUTO_LOG();
}

bool 
AudioSinkBase::AudioSinkThread::threadLoop()
{
    //AUTO_LOG();
    
    {
        AutoMutex _l(mMyLock);
        if (mPaused) {
            mMyCond.wait(mMyLock);
            // caller will check for exitPending()
            return true;
        }
        if (mIgnoreNextPausedInt) {
            mIgnoreNextPausedInt = false;
            mPausedInt = false;
        }        
        if (mPausedInt) {
            if (mPausedNs > 0) {
                (void) mMyCond.waitRelative(mMyLock, mPausedNs);
            } else {
                mMyCond.wait(mMyLock);
            }
            mPausedInt = false;
            return true;
        }        
    }    
    if (Thread::exitPending()) {
        return false;
    }
    nsecs_t ns = mReceiver.processAudioBuffer_l();
    switch (ns) {
    case 0:
        return true;
    case NS_INACTIVE:
        pauseInternal();
        return true;
    case NS_NEVER:
        return false;
    case NS_WHENEVER:
        // Event driven: call wake() when callback notifications conditions change.
        ns = INT64_MAX;
        // fall through
    default:
        LOG_ALWAYS_FATAL_IF(ns < 0, "processAudioBuffer() returned %d", ns);
        pauseInternal(ns);
        return true;
    }

    return true;
}

void        
AudioSinkBase::AudioSinkThread::requestExit()
{
    AUTO_LOG();
    
    // must be in this order to avoid a race condition
    Thread::requestExit();
    resume();
}

void        
AudioSinkBase::AudioSinkThread::pause()
{
    AUTO_LOG();
    
    AutoMutex _l(mMyLock);
    mPaused = true;
}

void        
AudioSinkBase::AudioSinkThread::resume()
{
    AUTO_LOG();
    
    AutoMutex _l(mMyLock);
    mIgnoreNextPausedInt = true;
    if (mPaused || mPausedInt) {
        mPaused = false;
        mPausedInt = false;
        mMyCond.signal();
    }
}

void        
AudioSinkBase::AudioSinkThread::wake()
{
    AUTO_LOG();
    
    AutoMutex _l(mMyLock);
    if (!mPaused) {
        // wake() might be called while servicing a callback - ignore the next
        // pause time and call processAudioBuffer.
        mIgnoreNextPausedInt = true;
        if (mPausedInt && mPausedNs > 0) {
            // audio track is active and internally paused with timeout.
            mPausedInt = false;
            mMyCond.signal();
        }
    }
}

void 
AudioSinkBase::AudioSinkThread::pauseInternal(nsecs_t ns)
{
    AUTO_LOG();
    
    AutoMutex _l(mMyLock);
    mPausedInt = true;
    mPausedNs = ns;
}

}  // namespace android
