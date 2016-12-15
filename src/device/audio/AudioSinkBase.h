
#ifndef _AUDIO_SINK_BASE_H_
#define _AUDIO_SINK_BASE_H_

#include <utils/Thread.h>
#include <media/MediaPlayerInterface.h>
#include <media/stagefright/foundation/ABase.h>

namespace android {

class AudioSinkBase : public MediaPlayerBase::AudioSink 
{
public:
        explicit AudioSinkBase();
        virtual ~AudioSinkBase();

        virtual bool        ready() const; // audio output is open and ready
        virtual ssize_t     bufferSize() const;
        virtual ssize_t     frameCount() const;
        virtual ssize_t     channelCount() const;
        virtual ssize_t     frameSize() const;
        virtual uint32_t    latency() const;
        virtual float       msecsPerFrame() const;
        virtual status_t    getPosition(uint32_t *position) const;
        virtual status_t    getTimestamp(AudioTimestamp &ts) const;
        virtual int64_t     getPlayedOutDurationUs(int64_t nowUs) const;
        virtual status_t    getFramesWritten(uint32_t *frameswritten) const;
        virtual audio_session_t getSessionId() const;
        virtual audio_stream_type_t getAudioStreamType() const;
        virtual uint32_t    getSampleRate() const;
        virtual int64_t     getBufferDurationInUs() const;

        // If no callback is specified, use the "write" API below to submit
        // audio data.
        virtual status_t    open(
                uint32_t sampleRate, int channelCount, audio_channel_mask_t channelMask,
                audio_format_t format=AUDIO_FORMAT_PCM_16_BIT,
                int bufferCount=DEFAULT_AUDIOSINK_BUFFERCOUNT,
                AudioCallback cb = NULL,
                void *cookie = NULL,
                audio_output_flags_t flags = AUDIO_OUTPUT_FLAG_NONE,
                const audio_offload_info_t *offloadInfo = NULL,
                bool doNotReconnect = false,
                uint32_t suggestedFrameCount = 0);

        virtual status_t    start();

        /* Input parameter |size| is in byte units stored in |buffer|.
         * Data is copied over and actual number of bytes written (>= 0)
         * is returned, or no data is copied and a negative status code
         * is returned (even when |blocking| is true).
         * When |blocking| is false, AudioSink will immediately return after
         * part of or full |buffer| is copied over.
         * When |blocking| is true, AudioSink will wait to copy the entire
         * buffer, unless an error occurs or the copy operation is
         * prematurely stopped.
         */
        virtual ssize_t     write(const void* buffer, size_t size, bool blocking = true);

        virtual void        stop();
        virtual void        flush();
        virtual void        pause();
        virtual void        close();

        virtual status_t    setPlaybackRate(const AudioPlaybackRate& rate);
        virtual status_t    getPlaybackRate(AudioPlaybackRate* rate /* nonnull */);

protected:
        virtual status_t    createSink_l() = 0;
        virtual status_t    restoreTrack_l(const char *from) = 0;
        virtual bool        isOffloaded_l() const = 0;
        virtual uint32_t    updateAndGetPosition_l() = 0;
        virtual void        flush_l() = 0;

        // body of AudioTrackThread::threadLoop()
        // returns the maximum amount of time before we would like to run again, where:
        //      0           immediately
        //      > 0         no later than this many nanoseconds from now
        //      NS_WHENEVER still active but no particular deadline
        //      NS_INACTIVE inactive so don't run again until re-started
        //      NS_NEVER    never again
        static const nsecs_t NS_WHENEVER = -1, NS_INACTIVE = -2, NS_NEVER = -3;
        virtual nsecs_t processAudioBuffer_l() = 0;

        class AudioSinkThread : public Thread
        {
        public:
                AudioSinkThread(AudioSinkBase& receiver, bool bCanCallJava = false);
        
                // Do not call Thread::requestExitAndWait() without first calling requestExit().
                // Thread::requestExitAndWait() is not virtual, and the implementation doesn't do enough.
                virtual void        requestExit();

                void        pause();    // suspend thread from execution at next loop boundary
                void        resume();   // allow thread to execute, if not requested to exit
                void        wake();     // wake to handle changed notification conditions.
        
        private:
                void        pauseInternal(nsecs_t ns = 0LL);
                                        // like pause(), but only used internally within thread
        
                friend class AudioSinkBase;
                virtual bool        threadLoop();
                AudioSinkBase&      mReceiver;
                virtual ~AudioSinkThread();
                Mutex               mMyLock;    // Thread::mLock is private
                Condition           mMyCond;    // Thread::mThreadExitedCondition is private
                bool                mPaused;    // whether thread is requested to pause at next loop entry                
                bool                mPausedInt; // whether thread internally requests pause
                nsecs_t             mPausedNs;  // if mPausedInt then associated timeout, otherwise ignored
                bool                mIgnoreNextPausedInt;   // skip any internal pause and go immediately
                                        // to processAudioBuffer() as state may have changed
                                        // since pause time calculated.
        }; // AudioSinkThread

        void *                  mCookie;
        AudioCallback           mCblk;                  // re-load after mLock.unlock()
        sp<AudioSinkThread>     mAudioSinkThread;

        status_t                mStatus;

        // Indicates the current track state.  Protected by mLock.
        enum State {
                STATE_ACTIVE,
                STATE_STOPPED,
                STATE_PAUSED,
                STATE_PAUSED_STOPPING,
                STATE_FLUSHED,
                STATE_STOPPING,
        }                       mState;
        mutable Mutex           mLock;

        uint32_t                mSampleRate;
        int                     mChannelCount;
        audio_channel_mask_t    mChannelMask;
        audio_format_t          mFormat;
        int                     mBufferCount;
        audio_output_flags_t    mFlags;
        audio_offload_info_t    mOffloadInfo;
        bool                    mDoNotReconnect;
        uint32_t                mSuggestedFrameCount;

        DISALLOW_EVIL_CONSTRUCTORS(AudioSinkBase);
}; // AudioSinkBase

} // namespace android
#endif // _AUDIO_SINK_BASE_H_
