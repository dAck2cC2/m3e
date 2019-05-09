
#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_INET_H_ // [
#define _MSC_INET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

#if 0 ///defined(_WIN32)
# undef  nhtol
# undef  htonl
# undef  nhtos
# undef  htons

# define ntohl(x)    ( ((x) << 24) | (((x) >> 24) & 255) | (((x) << 8) & 0xff0000) | (((x) >> 8) & 0xff00) )
# define htonl(x)    ntohl(x)
# define ntohs(x)    ( (((x) << 8) & 0xff00) | (((x) >> 8) & 255) )
# define htons(x)    ntohs(x)
#endif

#define IN_LOOPBACK(a)  (a)

#ifdef __cplusplus
}
#endif

#endif // _MSC_INET_H_
