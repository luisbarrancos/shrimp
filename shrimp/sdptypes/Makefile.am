SUBDIRS = .

lib_LTLIBRARIES = libsdptypes.la

shrimpdir = $(pkgincludedir)/sdptypes
shrimp_HEADERS = \
sdptypes.h

libsdptypes_la_SOURCES = \
sdptypes.h \
sdpfile.cpp \
sdpstring.cpp

CXXFLAGS = -g -Wall -DG_LOG_DOMAIN=\"SDPTYPES\"
INCLUDES = @SHRIMP_GLIB_CFLAGS@
 
