
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

INITRC_API
int InitRC_entry(int argc, char** argv);

INITRC_API
void InitRC_run(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _INIT_RC_H

