# OpenSceneGraph Beginners Guide
# Chapter 4: Building Geometry Models
# Author: Wang Rui <wangray84 at gmail dot com>

cmake_minimum_required( VERSION 2.6 )

# passt für Pool 346 ! evtl andere Pfade
#set(GLUT_INCLUDE_DIR /usr/include/)
#set(GLUT_glut_LIBRARY /usr/lib/libglut.so)

project( project_helix )

find_package( OpenThreads )
find_package( osg )
find_package( osgDB )
find_package( osgUtil )
find_package( osgViewer )
find_package( GLUT )
find_package( OpenGL )

macro( config_project PROJNAME LIBNAME )
    include_directories( ${${LIBNAME}_INCLUDE_DIR} )
    target_link_libraries( ${PROJNAME} ${${LIBNAME}_LIBRARY} )
endmacro()



# TFA - Creating the famous OpenGL teapot
add_executable( project_helix
                project_helix.cpp )


config_project( project_helix OPENTHREADS )
config_project( project_helix OSG )
config_project( project_helix OSGDB )
config_project( project_helix OSGUTIL )
config_project( project_helix OSGVIEWER )
config_project( project_helix GLUT )
config_project( project_helix OpenGL )
#target_link_libraries( project_helix GL )
