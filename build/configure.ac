#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
#AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AC_INIT(tweetx,0.1,tweetx-dev@googlegroups.com)
AM_INIT_AUTOMAKE(-Wall)

AC_CONFIG_SRCDIR([src/libsrc/log/stream.cc])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

# Checks for libraries.
DLopenCheck=1
AC_CHECK_LIB([dl],[dlopen],[],[DLopenCheck=0])
if test $DLopenCheck == 0
then
  AC_MSG_ERROR([dlopen is not present])
else
  AC_MSG_NOTICE([dlopen is present. continue ..])

fi

NcursesCheck=1
AC_CHECK_LIB([ncurses],[newwin],[],[NcursesCheck=0])
if test $NcursesCheck == 0
then
   AC_MSG_ERROR([ncurses is not present. Please install ncurses-dev.])
else
  AC_MSG_NOTICE([ncurses is present. continue ..])
fi

SSLCheck=1
AC_CHECK_LIB([ssl],[SSL_new],[],[SSLCheck=0])
if test $SSLCheck == 0
then
  AC_MSG_ERROR([SSL lib is not present. Please install libssl-dev])
else
  AC_MSG_NOTICE([SSL is present. continue ..])
fi


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h stddef.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_TYPE_UINT16_T
AC_CHECK_TYPES([ptrdiff_t])

AC_CONFIG_MACRO_DIR(m4)
#Adding Tweetx Macros
#Libtool support

AC_LIBTOOL_WIN32_DLL
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL

# Checks for library functions.
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([atoi bzero memmove select socket strchr])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/apps/Makefile
                 src/libsrc/Makefile
                 src/libsrc/common/Makefile
                 src/libsrc/config/Makefile
                 src/libsrc/log/Makefile
                 src/libsrc/network/Makefile
                 src/libsrc/plugins/Makefile
                 src/libsrc/pluginutil/Makefile
                 src/libsrc/plugins/logger/Makefile
                 src/libsrc/plugins/sms/Makefile
                 src/libsrc/third-party/Makefile
                 src/libsrc/third-party/ticpp/Makefile
                 src/libsrc/tui/Makefile
                 src/libsrc/thread/Makefile
                 src/libsrc/timestamper/Makefile
                 src/libsrc/search/Makefile
                 src/libsrc/spellcheck/Makefile
                 src/libsrc/error/Makefile
                 src/libsrc/pluginarch/Makefile
                 tweetx.pc
                 src/libsrc/wrapper/Makefile])
AC_OUTPUT
