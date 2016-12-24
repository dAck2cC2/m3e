#ifndef _OPEN_AL_SINK_H_
#define _OPEN_AL_SINK_H_

#include <AudioSinkFactory.h>
#include <AudioSinkBase.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace android {

class OpenALSink : public AudioSinkBase 
{
public:
        explicit OpenALSink();
        virtual ~OpenALSink();

        virtual ssize_t     bufferSize() const;
        virtual status_t    getTimestamp(AudioTimestamp &ts) const;
        virtual int64_t     getPlayedOutDurationUs(int64_t nowUs) const;
        virtual status_t    getFramesWritten(uint32_t *frameswritten) const;
        virtual int64_t     getBufferDurationInUs() const;
        virtual status_t    getPosition(uint32_t *position) const;

protected:
        virtual status_t    createSink_l();
        virtual status_t    restoreTrack_l(const char *from);
        virtual bool        isOffloaded_l() const;
        virtual uint32_t    updateAndGetPosition_l();
        virtual nsecs_t     processAudioBuffer_l();
        virtual void        flush_l();
        virtual void        close_l();

private:
        status_t convertFormatType();

private:

#define OPENAL_SINK_BUFFER_COUNT  (4)

        struct {
            ALuint   src;
            ALuint   buf[OPENAL_SINK_BUFFER_COUNT];
            ALenum   fmt;
            ALsizei  frq;
            int      bits;
            uint32_t size;
            uint32_t pos;
        }           mAud;

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
