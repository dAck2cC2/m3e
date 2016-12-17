
//#define LOG_NDEBUG 0
#define LOG_TAG "AudioSinkFactory"
#include <utils/Log.h>
#include <AudioSinkFactory.h>
#include <media/stagefright/foundation/ADebug.h>

#include "DumpSink.h"

#ifdef ENABLE_AUDIO_OPENAL
#include "OpenALSink.h"
#endif // ENABLE_OPENAL

namespace android {

static int getDefaultPlayerType() 
{
    return AUDIO_SINK_DUMP;
}

ANDROID_SINGLETON_STATIC_INSTANCE(AudioSinkFactory);

AudioSinkFactory::AudioSinkFactory() : 
    sInitComplete(false)
{
    registerBuiltinFactories();
}

AudioSinkFactory::~AudioSinkFactory()
{

}

status_t 
AudioSinkFactory::registerFactory_l(IFactory* factory, const int type) 
{
    if (NULL == factory) {
        ALOGE("Failed to register AudioSinkFactory of type %d, factory is"
              " NULL.", type);
        return BAD_VALUE;
    }

    if (sFactoryMap.indexOfKey(type) >= 0) {
        ALOGE("Failed to register AudioSinkFactory of type %d, type is"
              " already registered.", type);
        return ALREADY_EXISTS;
    }

    if (sFactoryMap.add(type, factory) < 0) {
        ALOGE("Failed to register AudioSinkFactory of type %d, failed to add"
              " to map.", type);
        return UNKNOWN_ERROR;
    }

    return OK;
}

status_t 
AudioSinkFactory::registerFactory(IFactory* factory, const int type) 
{
    Mutex::Autolock lock_(&sLock);
    return registerFactory_l(factory, type);
}

void AudioSinkFactory::unregisterFactory(const int type) 
{
    Mutex::Autolock lock_(&sLock);
    sFactoryMap.removeItem(type);
}

#define GET_AUDIO_SINK_TYPE_IMPL(a...)                  \
    Mutex::Autolock lock_(&sLock);                      \
                                                        \
    int ret = 0;                                        \
    float bestScore = 0.0;                              \
                                                        \
    for (size_t i = 0; i < sFactoryMap.size(); ++i) {   \
                                                        \
        IFactory* v = sFactoryMap.valueAt(i);           \
        float thisScore;                                \
        CHECK(v != NULL);                               \
        thisScore = v->scoreFactory(a, bestScore);      \
        if (thisScore > bestScore) {                    \
            ret = sFactoryMap.keyAt(i);                 \
            bestScore = thisScore;                      \
        }                                               \
    }                                                   \
                                                        \
    if (0.0 == bestScore) {                             \
        ret = getDefaultPlayerType();                   \
    }                                                   \
                                                        \
    return ret;

int 
AudioSinkFactory::getAudioSinkType(const char* name) 
{
    GET_AUDIO_SINK_TYPE_IMPL(name);
}

#undef GET_AUDIO_SINK_TYPE_IMPL

sp<MediaPlayerBase::AudioSink> 
AudioSinkFactory::createSink(const int type)
{
    sp<MediaPlayerBase::AudioSink> p;
    IFactory* factory;
    Mutex::Autolock lock_(&sLock);

    if (sFactoryMap.indexOfKey(type) < 0) {
        ALOGE("Failed to create audio sink object of type %d, no registered"
              " factory", type);
        return p;
    }

    factory = sFactoryMap.valueFor(type);
    CHECK(NULL != factory);
    p = factory->createSink();

    if (p == NULL) {
        ALOGE("Failed to create audio sink object of type %d, create failed",
               type);
        return p;
    }

    return p;    
}

void 
AudioSinkFactory::registerBuiltinFactories() 
{
    if (sInitComplete) {
        return;
    }

    registerFactory_l(new DumpSinkFactory(),   AUDIO_SINK_DUMP);

#ifdef ENABLE_AUDIO_OPENAL    
    registerFactory_l(new OpenALSinkFactory(), AUDIO_SINK_OPENAL);
#endif // ENABLE_OPENAL

    sInitComplete = true;
}

}  // namespace android
