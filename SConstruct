# scons configuration file

import os

opts = Options([os.path.abspath('options.cache'), os.path.abspath('custom.py')])
opts.Add('fltk_include_path', 'Point to the fltk header files', '')
opts.Add('fltk_lib_path', 'Point to the fltk library files', '')

# OpenGL setup
env = Environment()
env.Append(CPPPATH = ['/usr/include/GL', '$fltk_include_path', '/usr/local/include/fltk/compat/'])
# OS X
#env.Append(CPPPATH = ['/System/Library/Frameworks/OpenGL.framework/Headers', '$fltk_include_path', '/usr/local/include/fltk/compat'])

conf = Configure(env)
if not conf.CheckCHeader('gl.h') or not conf.CheckCHeader('glu.h'):
	print 'Shrimp requires OpenGL and GLU'
	Exit(1)
env = conf.Finish()


# Check for FLTK 2


# Debug
final = Environment(CCFLAGS = '-O2')
debug = Environment(CCFLAGS = '-g -Wall')
#debug = Environment(CCFLAGS = '-g')


# TinyXML
StaticLibrary('tinyxml', Split("""
	src/miscellaneous/tinyxml/tinystr.cpp
	src/miscellaneous/tinyxml/tinyxml.cpp
	src/miscellaneous/tinyxml/tinyxmlerror.cpp
	src/miscellaneous/tinyxml/tinyxmlparser.cpp
"""))


# Shrimp
shrimp_files = Split("""
	src/application/shrimp.cpp
	src/application/ui_about.cpp
	src/application/ui_application_window.cpp
	src/application/ui_scene_view.cpp
	src/application/ui_scene_view_events.cpp
	src/application/ui_splash.cpp
	src/miscellaneous/misc_system_functions.cpp
	src/miscellaneous/misc_xml.cpp
	src/miscellaneous/logging.cpp
	src/shading/shader_block.cpp
	src/shading/scene.cpp
	src/shading/scene_blocks.cpp
	src/shading/scene_grouping.cpp
	src/shading/scene_serialization.cpp
	src/shading/scene_selection.cpp
	src/shading/rib_root_block.cpp
""")


debug.Program(target = 'shrimp', source = shrimp_files, LIBS = ['tinyxml', 'GL', 'GLU', 'X11', 'Xi', 'Xinerama', 'Xext', 'Xft', 'pthread', 'm', 'supc++', 'fltk2', 'fltk2_gl', 'fltk2_images', 'jpeg', 'png'], LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '$fltk_lib_path'], CPPPATH = ['src/application', 'src/miscellaneous', 'src/shading'])
# OS X
# debug.Program(target = 'shrimp', source = shrimp_files, LIBS = ['tinyxml', 'GL', 'GLU', 'X11', 'Xi', 'Xinerama', 'Xext', 'Xft', 'pthread', 'm', 'supc++', 'fltk2', 'fltk2_gl', 'fltk2_images', 'jpeg', 'png'], LINKFLAGS = ['-framework', 'Cocoa', '-framework', 'AGL', '-framework', 'OpenGL', '-framework', 'Carbon'], LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '/opt/local/lib', '$fltk_lib_path'], CPPPATH = ['/usr/local/include/fltk/compat', '/System/Library/Frameworks/OpenGL.framework/Headers', 'src/application', 'src/miscellaneous', 'src/shading'])

SourceSignatures('timestamp')

