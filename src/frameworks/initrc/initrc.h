
#ifndef _ANDROID_INIT_RC_H
#define _ANDROID_INIT_RC_H

#include <cutils/compiler.h>
#include <utils/Singleton.h>

namespace android {

class ANDROID_API InitRC : public Singleton<InitRC>
{
public:
    InitRC();
    ~InitRC();
private:
    void ResetProperties();
    void StartServices();
};
    
}; // namespace android

#endif // _ANDROID_INIT_RC_H

