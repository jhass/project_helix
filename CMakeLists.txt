cmake_minimum_required( VERSION 2.6 )

# Nicht hier sondern CMakeLists.txt.local anlegen und dort ändern
#set(GLUT_INCLUDE_DIR /usr/include/)
#set(GLUT_glut_LIBRARY /usr/lib/libglut.so)

project( project_helix )

add_executable( project_helix
                project_helix.cpp

                views/MainView.cpp
                
                scenes/MainScene.cpp
                
                objects/ship.cpp 
                objects/nebula.cpp
                objects/asteroid.cpp
                objects/sphere.cpp
                objects/torus.cpp
                
                interactors/KeyboardEventHandler.cpp

                util.cpp)

add_executable( sphere
                objects/sphere.cpp
                runners/sphere.cpp )

add_executable( torus
                3rdparty/osgToy/Normals.cpp
                objects/torus.cpp
                runners/torus.cpp )

add_executable( asteroid
                objects/asteroid.cpp
                runners/asteroid.cpp )

add_executable( sun
				        objects/sphere.cpp
				        objects/sun.cpp
				        runners/sun.cpp	)

add_executable( rotator
                objects/rotator.cpp
                runners/rotator.cpp )
                
if( EXISTS CMakeLists.txt.local )
  include( CMakeLists.txt.local )
endif()

macro( config_project PROJNAME LIBNAME )
    include_directories( ${${LIBNAME}_INCLUDE_DIR} )
    target_link_libraries( ${PROJNAME} ${${LIBNAME}_LIBRARY} )
endmacro()

find_package( OpenThreads )
find_package( osg )
find_package( osgGA )
find_package( osgDB )
find_package( osgParticle )
find_package( osgUtil )
find_package( osgViewer )
find_package( GLUT )
find_package( OpenGL )

foreach( executable project_helix sphere torus asteroid sun rotator)

  config_project( ${executable} OPENTHREADS )
  config_project( ${executable} OSG )
  config_project( ${executable} OSGGA )
  config_project( ${executable} OSGDB )
  config_project( ${executable} OSGUTIL )
  config_project( ${executable} OSGPARTICLE )
  config_project( ${executable} OSGVIEWER )
  config_project( ${executable} GLUT )
  config_project( ${executable} OPENGL )
endforeach()
