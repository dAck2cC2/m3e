#ifndef ANDROID_UI_COMPILER_H
#define ANDROID_UI_COMPILER_H

#ifndef ANDROID_UI_API
#if defined(_MSC_VER)
#if ANDROID_UI_IMPLEMENTATION
#define ANDROID_UI_API __declspec(dllexport)
#else
#define ANDROID_UI_API __declspec(dllimport)
#endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#define ANDROID_UI_API __attribute__((visibility("default")))
#else
#define ANDROID_UI_API
#endif
#endif // ANDROID_UI_API

#endif // ANDROID_UI_COMPILER_H
