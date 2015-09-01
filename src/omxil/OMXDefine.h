#ifndef __OMX_DEFINE_H__
#define __OMX_DEFINE_H__


#include "engine/EngineDefine.h"


#define _OMX_BEGIN  ENGINE_BEGIN
#define _OMX_END    ENGINE_END
#define _OMX_NAME   ENGINE


/******************************************/
// ENABLE
/******************************************/

#ifndef ENABLE_CUSTOMISE
#define ENABLE_CUSTOMISE
#endif // ENABLE_CUSTOMISE

/******************************************/
// DISABLE
/******************************************/

#ifdef ENABLE_BINDER
#undef ENABLE_BINDER
#endif // ENABLE_BINDER


#ifdef ENABLE_VIDEO
#undef ENABLE_VIDEO
#endif // ENABLE_VIDEO

#endif // __OMX_DEFINE_H__

