AC_INIT(src/shrimp.cc)

AM_INIT_AUTOMAKE(shrimp,0.4.2)

AC_PREFIX_DEFAULT(/usr/local/shrimp)

AC_LANG_CPLUSPLUS
AC_PROG_CXX

AC_DISABLE_STATIC
AM_PROG_LIBTOOL

SHRIMP_CHECK_PLATFORM
SHRIMP_CHECK_OPENGL
SHRIMP_CHECK_OPENGLU

SHRIMP_COMPILER_FLAGS

SHRIMP_WITH_GTK

AC_CONFIG_FILES([
Makefile \
sdpgtk/Makefile \
sdptypes/Makefile \
sdpxml/Makefile \
src/Makefile \
]) 

AC_OUTPUT

AC_MSG_NOTICE([

Configuration complete ... now run

	make

to build the project.
])

