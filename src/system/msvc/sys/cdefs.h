/*
* Copyright (c) 1991 The Regents of the University of California.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 3. All advertising materials mentioning features or use of this software
*    must display the following acknowledgement:
*	This product includes software developed by the University of
*	California, Berkeley and its contributors.
* 4. Neither the name of the University nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*
*	@(#)cdefs.h	7.6 (Berkeley) 5/4/91
*/

#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#ifndef	_CDEFS_H_
#define	_CDEFS_H_

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
It must NOT include windows.h in this header file, 
because it may be included before winsock2.h.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* #include <windows.h> */

#ifndef __BEGIN_DECLS
#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	};
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif 

/*
* The __CONCAT macro is used to concatenate parts of symbol names, e.g.
* with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
* The __CONCAT macro is a bit tricky -- make sure you don't put spaces
* in between its arguments.  __CONCAT can also concatenate double-quoted
* strings produced by the __STRING macro, but this only works with ANSI C.
*/
#if defined(__STDC__) || defined(__cplusplus)
#define	__P(protos)	protos		/* full-blown ANSI C */
#define	__CONCAT(x,y)	x ## y
#define	__STRING(x)	#x

#else	/* !(__STDC__ || __cplusplus) */
#define	__P(protos)	()		/* traditional C preprocessor */
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"

#ifdef __GNUC__
#define	const		__const		/* GCC: ANSI C with -traditional */
#define	inline		__inline
#define	signed		__signed
#define	volatile	__volatile

#elif defined(_MSC_VER)
/* keep ANSI C keywords */

#else	/* !__GNUC__ */
#define	const				/* delete ANSI C keywords */
#define	inline
#define	signed
#define	volatile
#endif	/* !__GNUC__ */
#endif	/* !(__STDC__ || __cplusplus) */

#include <intrin.h>
#include <stdint.h>

#include "msvc_export.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CFG_NO_POPCNT)
#define __builtin_popcount   __popcnt
#define __builtin_popcountl  __popcnt
#define __builtin_popcountll __popcnt
#endif

#define __builtin_ctzl  __builtin_ctz
#define __builtin_ctzll __builtin_ctz
MSVC_EXPORT uint32_t __builtin_ctz(uint32_t value);

#  define __builtin_clzl  __builtin_clz
#  define __builtin_clzll __builtin_clz
MSVC_EXPORT uint32_t __builtin_clz(uint32_t value);

MSVC_EXPORT extern int ffs(int valu);

#ifdef __cplusplus
}
#endif

#endif /* !_CDEFS_H_ */
