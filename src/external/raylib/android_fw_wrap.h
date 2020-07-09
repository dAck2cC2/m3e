#ifndef ANDROID_FW_WRAP_H
#define ANDROID_FW_WRAP_H

#ifdef __cplusplus
extern "C" {
#endif

struct ANativeWindow;
typedef struct ANativeWindow ANativeWindow;

int AndroidFW_getFramebufferSize(ANativeWindow* win, int* w, int* h);

#ifdef __cplusplus
};
#endif

#endif // ANDROID_FW_WRAP_H
