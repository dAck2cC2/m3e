#ifndef SCRIPT_C_SATURATION_ARGB_H_
#define SCRIPT_C_SATURATION_ARGB_H_

#include "util/RefBase.h"

namespace android {

class ScriptC_saturationARGB : public RSC::RefBase
{
public:
    ScriptC_saturationARGB(RSC::sp<RSC::RS>& RS) {};
    void set_gSaturation(float f) {};
    void forEach_root(RSC::sp<RSC::Allocation>& in, RSC::sp<RSC::Allocation>& out) {};
protected:
    ~ScriptC_saturationARGB() {};
};

}   // namespace android

#endif // SCRIPT_C_SATURATION_ARGB_H_
