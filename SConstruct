# scons configuration file

import os, platform


# Optional FLTK 2 paths
vars = Variables('custom.py')
vars.Add(PathVariable('fltk_include_path', 'Point to the fltk header files', '', PathVariable.PathAccept))
vars.Add(PathVariable('fltk_lib_path', 'Point to the fltk library files', '', PathVariable.PathAccept))


# OpenGL setup
env = Environment(variables = vars)

if platform.system() == 'Linux':
	env.Append(CPPPATH = ['/usr/include/GL', '$fltk_include_path', '/usr/local/include/fltk/compat/'])
elif platform.system() == 'Darwin':
# OS X
	env.Append(CPPPATH = ['/System/Library/Frameworks/OpenGL.framework/Headers', '$fltk_include_path', '/usr/local/include/fltk/compat'])
else:
	print "Unknown platform: " + platform.system()
	Exit(1)


# Check GL headers
conf = Configure(env)
if not conf.CheckCHeader('gl.h') or not conf.CheckCHeader('glu.h'):
	print 'Shrimp requires OpenGL and GLU'
	Exit(1)
env = conf.Finish()

# Check FLTK 2 headers
conf = Configure(env)
if not conf.CheckCXXHeader('fltk/run.h'):
	print 'Shrimp requires FLTK 2'
	Exit(1)
env = conf.Finish()


# Debug
final = Environment(CCFLAGS = '-O2')
debug = Environment(CCFLAGS = '-g -Wall')


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
	src/shading/preferences.cpp
	src/shading/shader_block.cpp
	src/shading/scene.cpp
	src/shading/scene_blocks.cpp
	src/shading/scene_grouping.cpp
	src/shading/scene_serialization.cpp
	src/shading/scene_selection.cpp
	src/shading/rib_root_block.cpp
""")


if platform.system() == 'Linux':
	debug.Program(target = 'shrimp', source = shrimp_files, LIBS = ['tinyxml', 'GL', 'GLU', 'X11', 'Xi', 'Xext', 'Xft', 'Xinerama', 'pthread', 'm', 'supc++', 'fltk2', 'fltk2_gl', 'fltk2_images', 'jpeg', 'png'], LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '$fltk_lib_path'], CPPPATH = ['src/application', 'src/miscellaneous', 'src/shading'])
elif platform.system() == 'Darwin':
	debug.Program(target = 'shrimp', source = shrimp_files, LIBS = ['tinyxml', 'GL', 'GLU', 'X11', 'Xi', 'Xext', 'pthread', 'm', 'supc++', 'fltk2', 'fltk2_gl', 'fltk2_images', 'jpeg', 'png'], LINKFLAGS = ['-framework', 'Cocoa', '-framework', 'AGL', '-framework', 'OpenGL', '-framework', 'Carbon'], LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '/opt/local/lib', '$fltk_lib_path'], CPPPATH = ['/usr/local/include/fltk/compat', '/System/Library/Frameworks/OpenGL.framework/Headers', 'src/application', 'src/miscellaneous', 'src/shading'])


# File change test
Decider('timestamp-match')

