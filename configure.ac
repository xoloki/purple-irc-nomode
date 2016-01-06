AC_INIT([purple-irc-nomode], [1.0.0], [dragon@dancingdragon.be])
AC_CANONICAL_SYSTEM
AM_CONFIG_HEADER(plugin_config.h)

AM_INIT_AUTOMAKE([foreign dist-bzip2])

AC_PREREQ([2.50])

AC_DISABLE_STATIC

LT_INIT
LT_LANG([C])
LIBTOOL="$LIBTOOL --silent"

AC_DEFINE_UNQUOTED(PLUGIN_VERSION, "AC_PACKAGE_VERSION", [Plugin Version])
AC_DEFINE_UNQUOTED(PLUGIN_WEBSITE, "http://github.com/xoloki/purple-irc-nomode", [Plugin Website]) 

dnl #######################################################################
dnl # Our header
dnl #######################################################################
AH_TOP([ /* our header */
#ifndef PLUGIN_CONFIG_H
#define PLUGIN_CONFIG_H
])
AH_BOTTOM([
#endif /* PLUGIN_CONFIG_H */
])

dnl #######################################################################
dnl # Look for the C compiler
dnl #######################################################################
CFLAGS_save="$CFLAGS"
AC_PROG_CC
CFLAGS="$CFLAGS_save"

AC_ARG_ENABLE(debug, [  --enable-debug          compile with debugging support],,enable_debug=no)

if test "x$enable_debug" = "xyes" ; then
	AC_DEFINE(DEBUG, 1, [Define if debugging is enabled.])
fi

if test "x$GCC" = "xyes"; then
	CFLAGS="$CFLAGS -Wall -g3"
fi
AC_SUBST(CFLAGS)

dnl #######################################################################
dnl # Check for purple
dnl #######################################################################
PKG_CHECK_MODULES(PURPLE, purple,
[
	AC_DEFINE(HAVE_PURPLE, 1, [Define if we've found libpurple.])
])

HAVE_PURPLE="yes"
AM_CONDITIONAL(HAVE_PURPLE, true)
DEPENDENCIES="$DEPENDENCIES,purple"

if test x"$prefix" = x"NONE" ; then
    PURPLE_LIBDIR=`pkg-config --variable=libdir purple`
    PURPLE_DATADIR=`pkg-config --variable=datadir purple`
else
	PURPLE_LIBDIR="$libdir"
	PURPLE_DATADIR="$datadir"
fi

if test x"$PURPLE_LIBDIR" != x"" ; then
    PURPLE_LIBDIR="$PURPLE_LIBDIR/purple-2"
fi

AC_ARG_ENABLE(per-user-plugins, [  --enable-per-user-plugins          install to the ~/.purple/plugins],enable_per_user_plugins=yes,enable_per_user_plugins=no)

if test "x$enable_per_user_plugins" = "xyes" ; then
    PURPLE_LIBDIR="$HOME/.purple/plugins"
    PURPLE_DATADIR="$PURPLE_LIBDIR"
fi

AC_SUBST(PURPLE_CFLAGS)
AC_SUBST(PURPLE_LIBS)
AC_SUBST(PURPLE_LIBDIR)
AC_SUBST(PURPLE_DATADIR)

dnl #######################################################################
dnl # check for glib
dnl #######################################################################
HAVE_GLIB="no"
PKG_CHECK_MODULES(GLIB, [glib-2.0], HAVE_GLIB="yes", HAVE_GLIB="no")

if test x"$HAVE_GLIB" = x"no" ; then
	echo "glib development headers were not found.  glib development headers"
	echo "are required to build $PACKAGE."
	exit 1
fi
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

dnl #######################################################################
dnl # Check for some basic headers
dnl #######################################################################
AC_CHECK_HEADERS(regex.h)

dnl #######################################################################
dnl # Version stuff
dnl #######################################################################
AC_CONFIG_COMMANDS_PRE([
	if test -e VERSION; then
		cp -p VERSION VERSION.ac-save
	fi
])

AC_CONFIG_COMMANDS_POST([
	cmp VERSION VERSION.ac-save || touch -r VERSION.ac-save VERSION
	rm -f VERSION.ac-save
])

dnl #######################################################################
dnl # Finish up
dnl #######################################################################
AC_OUTPUT([Makefile
		   VERSION
		   src/Makefile
])

dnl #######################################################################
dnl # Ouput!!
dnl #######################################################################
echo;
echo $PACKAGE $VERSION Configuration complete
echo;
echo Debugging enabled................: $enable_debug
echo;

echo Build purple plugins.............: $HAVE_PURPLE
if test x"$HAVE_PURPLE" = x"yes" ; then
	echo Installing purple plugins to.....: `eval eval echo $PURPLE_LIBDIR`
	echo Installing purple plugin data to.: `eval eval echo $PURPLE_DATADIR`
fi
echo;

echo Type make to compile
echo;
