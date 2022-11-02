#
# EigenGap: Use the Eigen C++ Library within GAP
#
# This file is part of the build system of a GAP kernel extension.
# Requires GNU autoconf, GNU automake and GNU libtool.
#

dnl ##
dnl ## Setup autoconf
dnl ##
AC_PREREQ([2.68])
AC_INIT([EigenGap], m4_esyscmd([tr -d '\n' < PACKAGEVERSION]))
AC_CONFIG_SRCDIR([src/EigenGap.cc])
AC_CONFIG_HEADERS([src/pkgconfig.h:cnf/pkgconfig.h.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([cnf])

dnl ##
dnl ## Get canonical host info
dnl ##
AC_CANONICAL_HOST

dnl ##
dnl ## Setup automake
dnl ##
AM_INIT_AUTOMAKE([1.11 -Wall foreign subdir-objects])
AM_SILENT_RULES([yes])
AM_PROG_AR

dnl ##
dnl ## Set the language
dnl ##
AC_PROG_CXX
AC_LANG([C++])

dnl ##
dnl ## Setup libtool (for building the GAP kernel extension)
dnl ##
LT_PREREQ([2.4.2])
LT_INIT([disable-static dlopen win32-dll])

dnl ##
dnl ## Locate the GAP root dir
dnl ##
FIND_GAP

dnl ##
dnl ## Detect pointer size to distinguish 32 and 64 bit builds
dnl ##
AC_CHECK_SIZEOF([void **])

EIGEN="./eigen/"
EIGEN_CPPFLAGS="-I$EIGEN"
EIGEN_LDPATH="$EIGEN"
EIGEN_LDFLAGS="-L$EIGEN_LDPATH"
AC_SUBST(EIGEN_LDPATH)
AC_SUBST(EIGEN_LDFLAGS)
AC_SUBST(EIGEN_CPPFLAGS)

dnl ##
dnl ## Detect Windows resp. Cygwin
dnl ##
case $host_os in
  *cygwin* ) CYGWIN=yes;;
         * ) CYGWIN=no;;
esac
AM_CONDITIONAL([SYS_IS_CYGWIN], [test "$CYGWIN" = "yes"])

dnl ##
dnl ## Rebuild configure if VERSION file changes
dnl ##
AC_SUBST([CONFIG_STATUS_DEPENDENCIES], ['$(top_srcdir)/PACKAGEVERSION'])

dnl ##
dnl ## Output everything
dnl ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
