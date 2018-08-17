
#ifndef _ANDROID_INIT_RC_H
#define _ANDROID_INIT_RC_H

#include <cutils/compiler.h>
#include <utils/Singleton.h>

namespace android {

class ANDROID_API_INITRC InitRC : public Singleton<InitRC>
{
public:
    status_t Entry(int argc, char** argv);
    void Run();
    
private:
    friend Singleton;
    
    InitRC();
    ~InitRC();
    
    void ResetProperties();
    void StartService(int index);
};
    
ANDROID_SINGLETON_STATIC_INSTANCE(InitRC);

}; // namespace android

#endif // _ANDROID_INIT_RC_H

