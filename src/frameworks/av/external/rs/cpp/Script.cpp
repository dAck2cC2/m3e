
#include "RenderScript.h"

using namespace android;
using namespace RSC;

void Script::invoke(uint32_t slot, const void *v, size_t len) const {
}

void Script::forEach(uint32_t slot, sp<const Allocation> ain, sp<const Allocation> aout,
                       const void *usr, size_t usrLen) const {
}

Script::Script(void *id, sp<RS> rs) : BaseObj(id, rs) {
}


void Script::bindAllocation(sp<Allocation> va, uint32_t slot) const {
}


void Script::setVar(uint32_t index, sp<const BaseObj> o) const {
}

void Script::setVar(uint32_t index, const void *v, size_t len) const {
}

void Script::FieldBase::init(sp<RS> rs, uint32_t dimx, uint32_t usages) {
}
