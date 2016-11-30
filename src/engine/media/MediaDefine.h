
#ifndef __MEDIA_DEFINE_H__
#define __MEDIA_DEFINE_H__

#include "engine/EngineDefine.h"

#define _MEDIA_BEGIN  ENGINE_BEGIN
#define _MEDIA_END    ENGINE_END

/*******************************************/
// ENABLE
/*******************************************/

#ifndef ENABLE_CUSTOMISE
#define ENABLE_CUSTOMISE
#endif // ENABLE_CUSTOMISE

/*******************************************/
// DISABLE
/*******************************************/

#ifdef ENABLE_SKIP_LIST
#undef ENABLE_SKIP_LIST
#endif // ENABLE_SKIP_LIST

#ifdef ENABLE_DRM_EXTRACTOR
#undef ENABLE_DRM_EXTRACTOR
#endif // ENABLE_DRM_EXTRACTOR

#ifdef ENABLE_ALL_EXTRACTOR
#undef ENABLE_ALL_EXTRACTOR
#endif // ENABLE_ALL_EXTRACTOR


#endif // __MEDIA_DEFINE_H__

