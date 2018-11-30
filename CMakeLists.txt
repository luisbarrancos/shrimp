cmake_minimum_required(VERSION 3.10)


project(shrimp VERSION 1.0 LANGUAGES CXX)

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message (FATAL_ERROR "Not allowed to run in-source build!")
endif ()

# Build type menus
set (CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo"
     CACHE STRING "" FORCE)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Debug
         CACHE STRING
         "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}"
         FORCE
    )
    set_property (CACHE CMAKE_BUILD_TYPE
                  PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES}
    )
endif ()

option (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type
if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions (-DNDEBUG -O3)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_definitions (-g3 -ggdb3 -O3)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions (-g3 -ggdb3 -O0)
else ()
	add_definitions (-O2)
endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


# C++ standard to use
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11")
add_definitions ("-std=c++11")

option (CMAKE_VERBOSE_MAKEFILE ON)

set (QT_MIN_VERSION 4.8.0)
find_package (Qt4 REQUIRED)
set (QT_USE_QTOPENGL true)

include (${QT_USE_FILE})

include_directories (
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
	${QT_QTCORE_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
	${QT_QTOPENGL_INCLUDE_DIR}
)

set (LIBS ${QT_QTCORE_LIBRARY}
		  ${QT_QTGUI_LIBRARY}
		  ${QT_QTCORE_LIBRARY}
		  ${QT_QTGUI_LIBRARY}
		  ${QT_QTOPENGL_LIBRARY}
)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
	message (STATUS "Looking for OpenGL - found")
	include_directories (${OPENGL_INCLUDE_PATH})
	set (LIBS ${LIBS} ${OPENGL_LIBRARIES})
else ()
	message (SEND_ERROR "Looking for OpenGL - not found")
endif ()

set (shrimp_HDRS
	src/miscellaneous/tinyxml/tinystr.h
	src/miscellaneous/tinyxml/tinyxml.h
	src/miscellaneous/logging.h
	src/miscellaneous/misc_xml.h
	src/miscellaneous/misc_string_functions.h
	src/shading/preferences.h
	src/shading/rib_root_block.h
	src/shading/rib_root_block_parsing.h
	src/shading/scene.h
	src/shading/shader_block.h
	src/shading/shrimp_public_structures.h
	src/opengl_view/opengl_view.h
	src/services.h
	src/interfaces/i_opengl_texture.h
	src/interfaces/i_system_functions.h
)

set (shrimp_SRCS
	src/application-qt4/scene_view.cpp
	src/application-qt4/shrimp.cpp
	src/application-qt4/application_window.cpp
	src/application-qt4/system_functions.cpp
	src/application-qt4/shader_properties.cpp
	src/application-qt4/code_preview.cpp
	src/application-qt4/options.cpp
	src/application-qt4/block_code.cpp
	src/application-qt4/block_info.cpp
	src/application-qt4/block_input_output.cpp
	src/application-qt4/block_name.cpp
	src/application-qt4/rib_block.cpp
	src/miscellaneous/tinyxml/tinystr.cpp
	src/miscellaneous/tinyxml/tinyxml.cpp
	src/miscellaneous/tinyxml/tinyxmlerror.cpp
	src/miscellaneous/tinyxml/tinyxmlparser.cpp
	src/miscellaneous/logging.cpp
	src/miscellaneous/misc_xml.cpp
	src/shading/preferences.cpp
	src/shading/rib_root_block.cpp
	src/shading/rib_root_block_parsing.cpp
	src/shading/scene_blocks.cpp
	src/shading/scene.cpp
	src/shading/scene_grouping.cpp
	src/shading/scene_serialization.cpp
	src/shading/shader_block.cpp
	src/opengl_view/opengl_view.cpp
	src/opengl_view/draw.cpp
	src/services.cpp
)

set (shrimp_UIS
	src/application-qt4/application_window.ui
	src/application-qt4/shader_properties.ui
	src/application-qt4/code_preview.ui
	src/application-qt4/options.ui
	src/application-qt4/block_info.ui
	src/application-qt4/block_name.ui
	src/application-qt4/block_code.ui
	src/application-qt4/block_input_output.ui
	src/application-qt4/rib_block.ui
)

QT4_WRAP_UI(UIS ${shrimp_UIS})

set (shrimp_MOCS
	src/application-qt4/scene_view.h
	src/application-qt4/application_window.h
	src/application-qt4/system_functions.h
	src/application-qt4/shader_properties.h
	src/application-qt4/code_preview.h
	src/application-qt4/options.h
	src/application-qt4/block_code.h
	src/application-qt4/block_info.h
	src/application-qt4/block_input_output.h
	src/application-qt4/block_name.h
	src/application-qt4/rib_block.h
)

QT4_WRAP_CPP(MOCS ${shrimp_MOCS})

add_executable (shrimp ${shrimp_SRCS}
					   ${UIS}
					   ${RSCS}
					   ${TRS}
					   ${MOCS}
)

target_link_libraries (shrimp ${LIBS})
