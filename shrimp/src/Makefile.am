bin_PROGRAMS = shrimp
shrimp_SOURCES = shrimp.cc \
 block.h \
 block.cc \
 block_ops.cc \
 blockhelp.h \
 blockhelp.cc \
 circuit.h \
 circuit.cc \
 circuit_ops.cc \
 codepreview.h \
 codepreview.cc \
 gridentity.h \
 helpers.h \
 helpers.cc \
 iopad.h \
 iopad.cc \
 ioproperties.h \
 ioproperties.cc \
 mainwindow.h \
 mainwindow.cc \
 modaldialog.h \
 modaldialog.cc \
 renderoptions.h \
 renderoptions.cc \
 resizedialog.h \
 resizedialog.cc \
 shaderprop.h \
 shaderprop.cc

CXXFLAGS = -Wall -DLOG_DOMAIN=\"SHRIMP\"
INCLUDES = -I$(top_srcdir) @SHRIMP_GTK_CFLAGS@ @SHRIMP_GLIB_CFLAGS@
LDFLAGS = $(top_builddir)/sdpgtk/libsdpgtk.la $(top_builddir)/sdpxml/libsdpxml.la $(top_builddir)/sdptypes/libsdptypes.la @SHRIMP_OPENGLU_LIBS@ @SHRIMP_OPENGL_LIBS@ @SHRIMP_GTK_LIBS@ @SHRIMP_GLIB_LIBS@


