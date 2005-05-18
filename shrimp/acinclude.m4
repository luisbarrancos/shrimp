########################################################
# SHRIMP_CHECK_PLATFORM - tests to see what platform we're building on - posix, win32, darwin, etc.

AC_DEFUN([SHRIMP_CHECK_PLATFORM], [
AC_MSG_CHECKING([for platform])
AC_ARG_WITH(win32-prefix,[  --with-win32-prefix[[=PATH]]    change location of win32 libs [[/c/Projects/shrimp-win32]]],[],[withval=/c/Projects/shrimp-win32])
if test x$withval != x; then
	shrimp_win32_prefix=$withval
fi

case $host in
  *-*-cygwin* | *-*-mingw*)
	AC_MSG_RESULT([found Win32 native (cygwin or mingw)])
	shrimp_win32=true 
	LDFLAGS="-no-undefined -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--enable-runtime-pseudo-reloc"
	AC_DEFINE([SHRIMP_PLATFORM_WIN32_NATIVE], [1], [Define to 1 if you are building Shrimp on Win32 (cygwin or mingw)])
	;;
  *-*-darwin*)
  	AC_MSG_RESULT([found Darwin (including Mac OS-X)])
	AC_DEFINE([SHRIMP_PLATFORM_DARWIN], [1], [Define to 1 if you are building Shrimp on Darwin (including Mac OS-X)])
	;;
  *)
	AC_MSG_RESULT([defaulting to posix])
	shrimp_win32=false 
	AC_DEFINE([SHRIMP_PLATFORM_POSIX], [1], [Define to 1 if you are building Shrimp on most Posix platforms, including GNU/Linux])
	;;

esac
AM_CONDITIONAL(SHRIMP_WIN32, test x$shrimp_win32 = xtrue)
])

########################################################
# SHRIMP_COMPILER_FLAGS

AC_DEFUN(SHRIMP_COMPILER_FLAGS, [
AC_SUBST(SHRIMP_CFLAGS)
AC_SUBST(SHRIMP_CPPFLAGS)
AC_SUBST(SHRIMP_CXXFLAGS)

if $shrimp_win32; then
	SHRIMP_CFLAGS="-Wall"
	SHRIMP_CPPFLAGS="-I\$(top_srcdir) -I\$(top_srcdir)/boost"
	SHRIMP_CXXFLAGS="-Wall -Wno-ctor-dtor-privacy -mms-bitfields"
else
	SHRIMP_CFLAGS="-Wall"
	SHRIMP_CPPFLAGS="-I\$(top_srcdir) -I\$(top_srcdir)/boost"
	SHRIMP_CXXFLAGS="-Wall -Wno-ctor-dtor-privacy"
fi

])

########################################################
# SHRIMP_CHECK_OPENGL - tests for an installed OpenGL library

AC_DEFUN(SHRIMP_CHECK_OPENGL, [
AC_SUBST(SHRIMP_OPENGL_CFLAGS)
AC_SUBST(SHRIMP_OPENGL_LIBS)
AC_MSG_CHECKING([for OpenGL])

shrimp_check_opengl_lib_dir=""
shrimp_check_opengl_directories="/usr/lib /usr/local/lib /usr/X11R6/lib"
for shrimp_check_opengl_directory in $shrimp_check_opengl_directories; do
	if test -f $shrimp_check_opengl_directory/libGL.so || test -f $shrimp_check_opengl_directory/libGL.a; then
		shrimp_check_opengl_lib_dir=$shrimp_check_opengl_directory
	fi
done

shrimp_check_opengl_header_dir=""
shrimp_check_opengl_directories="/usr/include /usr/local/include /usr/X11R6/include"
for shrimp_check_opengl_directory in $shrimp_check_opengl_directories; do
	if test -f $shrimp_check_opengl_directory/GL/gl.h; then
		shrimp_check_opengl_header_dir=$shrimp_check_opengl_directory
	fi
done

if test -n $shrimp_check_opengl_lib_dir && test -n $shrimp_check_opengl_header_dir; then
	SHRIMP_OPENGL_CFLAGS="-I$shrimp_check_opengl_header_dir"
	SHRIMP_OPENGL_LIBS="-L$shrimp_check_opengl_lib_dir -lGL"
	AC_MSG_RESULT([found in $shrimp_check_opengl_lib_dir and $shrimp_check_opengl_header_dir])
else
	AC_MSG_ERROR([OpenGL required but not found])
fi

])

########################################################
# SHRIMP_CHECK_OPENGLU - tests for an installed OpenGLU library

AC_DEFUN(SHRIMP_CHECK_OPENGLU, [
AC_SUBST(SHRIMP_OPENGLU_CFLAGS)
AC_SUBST(SHRIMP_OPENGLU_LIBS)
AC_MSG_CHECKING([for OpenGLU])

shrimp_check_openglu_lib_dir=""
shrimp_check_openglu_directories="/usr/lib /usr/local/lib /usr/X11R6/lib"
for shrimp_check_openglu_directory in $shrimp_check_openglu_directories; do
	if test -f $shrimp_check_openglu_directory/libGLU.so || test -f $shrimp_check_openglu_directory/libGLU.a; then
		shrimp_check_openglu_lib_dir=$shrimp_check_openglu_directory
	fi
done

shrimp_check_openglu_header_dir=""
shrimp_check_openglu_directories="/usr/include /usr/local/include /usr/X11R6/include"
for shrimp_check_openglu_directory in $shrimp_check_openglu_directories; do
	if test -f $shrimp_check_openglu_directory/GL/gl.h; then
		shrimp_check_openglu_header_dir=$shrimp_check_openglu_directory
	fi
done

if test -n $shrimp_check_openglu_lib_dir && test -n $shrimp_check_openglu_header_dir; then
	SHRIMP_OPENGLU_CFLAGS="-I$shrimp_check_openglu_header_dir"
	SHRIMP_OPENGLU_LIBS="-L$shrimp_check_openglu_lib_dir -lGLU"
	AC_MSG_RESULT([found in $shrimp_check_openglu_lib_dir and $shrimp_check_openglu_header_dir])
else
	AC_MSG_ERROR([OpenGLU required but not found])
fi

])

########################################################
# SHRIMP_WITH_GTK - tests for an installed GTK+ library

AC_DEFUN([SHRIMP_WITH_GTK], [
AC_SUBST(SHRIMP_GLIB_CFLAGS)
AC_SUBST(SHRIMP_GLIB_LIBS)
AC_SUBST(SHRIMP_GTK_CFLAGS)
AC_SUBST(SHRIMP_GTK_LIBS)
AC_MSG_CHECKING([for GTK+])

if $shrimp_win32; then
	SHRIMP_GLIB_VERSION="glib-2.0"
	SHRIMP_GTK_VERSION="gtk-2.0"
	SHRIMP_GLIB_CFLAGS="-I$shrimp_win32_prefix/include -I$shrimp_win32_prefix/include/gtk -I$shrimp_win32_prefix/include/gdk -I$shrimp_win32_prefix/include/glib-2.0 -I$shrimp_win32_prefix/lib/gtk+/include -I$shrimp_win32_prefix/lib/glib-2.0/include"
	SHRIMP_GLIB_LIBS="-L$shrimp_win32_prefix/lib -lglib-2.0 -lgtk -lgdk -lgmodule-2.0"
else
	if [ ! glib-config --version >/dev/null 2>/dev/null ]; then
		AC_MSG_ERROR([glib required but not found])
	fi

	if [ ! gtk-config --version >/dev/null 2>/dev/null ]; then
		AC_MSG_ERROR([gtk required but not found])
	fi

	SHRIMP_GLIB_VERSION=`glib-config --version`
	SHRIMP_GLIB_CFLAGS=`glib-config --cflags`
	SHRIMP_GLIB_LIBS=`glib-config --libs`
	
	SHRIMP_GTK_VERSION=`gtk-config --version`
	SHRIMP_GTK_CFLAGS=`gtk-config --cflags`
	SHRIMP_GTK_LIBS=`gtk-config --libs`
fi

])

