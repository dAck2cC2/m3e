#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef _MSC_ENDIAN_H_ // [
#define _MSC_ENDIAN_H_

#if _MSC_VER > 1000
#pragma once
#endif

#define __BIG_ENDIAN     0x1000
#define __LITTLE_ENDIAN  0x0001
#define __BYTE_ORDER     __LITTLE_ENDIAN

#define BIG_ENDIAN       __BIG_ENDIAN 
#define LITTLE_ENDIAN    __LITTLE_ENDIAN 
#define BYTE_ORDER       __BYTE_ORDER


#endif // _MSC_ENDIAN_H_ ]
