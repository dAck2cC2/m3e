
#ifndef _AUDIO_SINK_FACTORY_H_
#define _AUDIO_SINK_FACTORY_H_

#include <utils/KeyedVector.h>
#include <utils/Singleton.h>
#include <media/MediaPlayerInterface.h>
#include <media/stagefright/foundation/ABase.h>

namespace android {

enum {
  AUDIO_SINK_DUMP = 0,
  AUDIO_SINK_OPENAL,
  AUDIO_SINK_CUSTOMISE = 100
};

class AudioSinkFactory : public Singleton<AudioSinkFactory>
{
    friend class Singleton<AudioSinkFactory>;
  
public:
    class IFactory {
    public:
        virtual ~IFactory() { }
        virtual float scoreFactory(const char* /*audio sink name*/,
                                   float /*curScore*/) { return 0.0; }
                                   
        virtual sp<MediaPlayerBase::AudioSink> createSink() = 0;
    }; // IFactory

    status_t registerFactory(IFactory* factory, const int type);
    void     unregisterFactory(const int type);

    int getAudioSinkType(const char* name);
    sp<MediaPlayerBase::AudioSink> createSink(const int type);

    virtual ~AudioSinkFactory();
private:
    explicit AudioSinkFactory();

    void     registerBuiltinFactories();
    status_t registerFactory_l(IFactory* factory, 
                               const int type);

    typedef KeyedVector<int, IFactory*> tFactoryMap;

    Mutex       sLock;
    tFactoryMap sFactoryMap;
    bool        sInitComplete;

    DISALLOW_EVIL_CONSTRUCTORS(AudioSinkFactory);
};

}  // namespace android
#endif  // _AUDIO_SINK_FACTORY_H_
