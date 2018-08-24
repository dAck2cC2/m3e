#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_DLFCN_H_ // [
#define _MSC_DLFCN_H_

#include <windows.h>

#define dlopen(a, b) LoadLibrary(a);
#define dlsym(a, b)  GetProcAddress((HMODULE)a, b);
#define dlclose(a)   FreeLibrary((HMODULE)a)
#define dlerror()    "MS Windows"

#endif // _MSC_DLFCN_H_ ]
