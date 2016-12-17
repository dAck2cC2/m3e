#ifndef _DUMP_SINK_H_
#define _DUMP_SINK_H_

#include <AudioSinkFactory.h>
#include <AudioSinkBase.h>

namespace android {

class DumpSink : public AudioSinkBase 
{
public:
        explicit DumpSink();
        virtual ~DumpSink();

protected:
        virtual status_t    createSink_l();
        virtual status_t    restoreTrack_l(const char *from);
        virtual bool        isOffloaded_l() const;
        virtual uint32_t    updateAndGetPosition_l();
        virtual nsecs_t     processAudioBuffer_l();
        virtual void        flush_l();       
        virtual void        close_l();

        DISALLOW_EVIL_CONSTRUCTORS(DumpSink);
};

class DumpSinkFactory : public AudioSinkFactory::IFactory 
{
public:
        explicit DumpSinkFactory() {};
        virtual ~DumpSinkFactory() {};

        virtual float scoreFactory(const char* name, float curSocre) {
            static const float kOurScore = 0.2;
            if (kOurScore <= curSocre) {
                return 0.0;
            }

            if (!strncasecmp("default", name, 7)) {
                return kOurScore;
            }

            if (!strncasecmp("dump", name, 4)) {
                return kOurScore;
            }

            return 0.0;
        };

        virtual sp<MediaPlayerBase::AudioSink> createSink() {
            return new DumpSink();
        };

        DISALLOW_EVIL_CONSTRUCTORS(DumpSinkFactory);        
};

} // namespace android
#endif // _DUMP_SINK_H_
