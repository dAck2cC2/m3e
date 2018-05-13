
#ifndef _ANDROID_INIT_RC_H
#define _ANDROID_INIT_RC_H

#include <cutils/compiler.h>
#include <utils/Singleton.h>

namespace android {

class ANDROID_API InitRC : public Singleton<InitRC>
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
    
}; // namespace android

#endif // _ANDROID_INIT_RC_H

