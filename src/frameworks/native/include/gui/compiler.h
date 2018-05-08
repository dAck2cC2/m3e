#ifndef ANDROID_GUI_COMPILER_H
#define ANDROID_GUI_COMPILER_H

#ifndef ANDROID_GUI_API
#if defined(_MSC_VER)
#if ANDROID_GUI_IMPLEMENTATION
#define ANDROID_GUI_API __declspec(dllexport)
#else
#define ANDROID_GUI_API __declspec(dllimport)
#endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#define ANDROID_GUI_API __attribute__((visibility("default")))
#else
#define ANDROID_GUI_API
#endif
#endif // ANDROID_GUI_API

#endif // ANDROID_GUI_COMPILER_H
