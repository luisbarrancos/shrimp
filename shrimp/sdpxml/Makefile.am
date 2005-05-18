SUBDIRS = .

lib_LTLIBRARIES = libsdpxml.la

shrimpdir = $(pkgincludedir)/sdpxml
shrimp_HEADERS = \
sdpxml.h

libsdpxml_la_SOURCES = \
sdpxml.cpp \
sdpxml.h \
sdpxmlsax.cpp

#libsdpxml_la_LDFLAGS = -version-info @LIB_VERSION@ 

CXXFLAGS = -g -Wall -DG_LOG_DOMAIN=\"SDPXML\"
INCLUDES = -I$(top_srcdir) @SHRIMP_GLIB_CFLAGS@
 

