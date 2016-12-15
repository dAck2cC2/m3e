#ifndef _OPEN_AL_SINK_H_
#define _OPEN_AL_SINK_H_

#include <AudioSinkFactory.h>
#include <AudioSinkBase.h>

namespace android {

class OpenALSink : public AudioSinkBase 
{
public:
        explicit OpenALSink();
        virtual ~OpenALSink();

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
        virtual status_t    createSink_l();
        virtual status_t    restoreTrack_l(const char *from);
        virtual bool        isOffloaded_l() const;
        virtual uint32_t    updateAndGetPosition_l();
        virtual void        flush_l();
        virtual nsecs_t     processAudioBuffer_l();

        DISALLOW_EVIL_CONSTRUCTORS(OpenALSink);
};

class OpenALSinkFactory : public AudioSinkFactory::IFactory 
{
public:
        explicit OpenALSinkFactory() {};
        virtual ~OpenALSinkFactory() {};

        virtual float scoreFactory(const char* name, float curSocre) {
            static const float kOurScore = 0.8;
            if (kOurScore <= curSocre) {
                return 0.0;
            }

            if (!strncasecmp("default", name, 7)) {
                return kOurScore;
            }

            if (!strncasecmp("openal", name, 6)) {
                return kOurScore;
            }

            return 0.0;
        };

        virtual sp<MediaPlayerBase::AudioSink> createSink() {
            return new OpenALSink();
        };

        DISALLOW_EVIL_CONSTRUCTORS(OpenALSinkFactory);        
};

} // namespace android
#endif // _OPEN_AL_SINK_H_
