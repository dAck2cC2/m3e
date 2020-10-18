
#ifndef _INIT_RC_H
#define _INIT_RC_H

#ifndef INITRC_API
    #ifdef __GNUC__
        #define INITRC_API                 /* override per-platform */
    #else
        #define INITRC_API __declspec(dllimport)
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define M_PROPERTY(name)  extern INITRC_API const char* const name

M_PROPERTY(M_PROPERTY_DISPLAY_NAME);
M_PROPERTY(M_PROPERTY_DISPLAY_WIDTH);
M_PROPERTY(M_PROPERTY_DISPLAY_HEIGHT);

M_PROPERTY(M_PROPERTY_BOOT_ANIMATION_TIME_SEC);

INITRC_API
int InitRC_set(const char* property, const char* value);

INITRC_API
int InitRC_entry(int argc, char** argv);

INITRC_API
void InitRC_run(void);

INITRC_API
void InitRC_waitForBootAnimation(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _INIT_RC_H

