#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Media Cube Engine], [0.1], [dAck2cC@yahoo.com], [m3e], [https://github.com/dAck2cC2/m3e])
AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADERS([3rd/lame/include/lame.h])
AC_LANG([C++])

# check system
AC_CANONICAL_HOST

# automake
AM_INIT_AUTOMAKE

AM_MAINTAINER_MODE
AM_MAKE_INCLUDE

AC_AIX
AC_ISC_POSIX
AC_MINIX
AC_MSG_RESULT(${host_os})
case $host_os in
  *cygwin* ) PLATFORM=cygwin;;
  *linux*  ) PLATFORM=linux;;
  *darwin* ) PLATFORM=osx;;
         * ) PLATFORM=linux;;
esac

#AC_ENABLE_SHARED
#AC_DISABLE_STATIC
#LT_INIT([dlopen])
#AC_DISABLE_STATIC
#AC_ENABLE_SHARED
#LT_LANG([C++])
AC_PROG_LIBTOOL
AC_SUBST([LIBTOOL_DEPS])
CFLAGS="${ac_save_CFLAGS}"
#AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
if test "${GCC}" = "yes"; then
	AC_MSG_CHECKING(version of GCC)
	GCC_version=`${GCC} --version | sed -n '1s/^[[^ ]]* (.*) //;s/ .*$//;1p'`
	AC_MSG_RESULT(${GCC_version})
fi


AC_PROG_CXX
#AC_PROG_RANLIB

# more automake stuff
#AM_C_PROTOTYPES


# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h memory.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/time.h unistd.h])

AC_C_CONST
AC_SYS_LARGEFILE
if test ${cross_compiling} = "no"; then
	AC_C_BIGENDIAN
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime gettimeofday memmove memset strcasecmp strchr strdup strerror strncasecmp strrchr strstr])

# initialize configuration variables for the Makefile
CFLAGS=${CFLAGS}
CONFIG_DEFS=${CONFIG_DEFS}
AM_CPPFLAGS="-I\$(top_srcdir)/3rd/lame/include -I\$(top_srcdir)/src"
LIB_SOURCE=
MAKEDEP="-M"

case $host_os in
  *cygwin* ) CFLAGS="-D_CYGWIN ${CFLAGS}";;
  *linux*  ) CFLAGS="-D_LINUX ${CFLAGS}";;
  *darwin* ) CFLAGS="-D_OSX ${CFLAGS}";;
         * ) CFLAGS="-D_LINUX ${CFLAGS}";;
esac

AC_SUBST(PLATFORM)
AC_SUBST(CFLAGS)
AC_SUBST(AM_CPPFLAGS)

AC_CONFIG_FILES([Makefile
                ])
#                 src/Makefile
#                 src/engine/Makefile
#                 src/impl/Makefile
#                 src/media/Makefile
#                 src/omxil/Makefile
#                 src/utils/Makefile
#                 ])
AC_OUTPUT
