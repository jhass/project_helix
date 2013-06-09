project( project_helix )

include_directories( . .. )

add_executable( project_helix
                project_helix.cpp

                views/MainView.cpp
                
                scenes/MainScene.cpp
                
                objects/Ship.cpp 
                objects/Nebula.cpp
                objects/Asteroid.cpp
                objects/Sphere.cpp
                objects/Torus.cpp
                
                interactors/KeyboardEventHandler.cpp

                util.cpp )

add_executable( sphere
                objects/Sphere.cpp
                runners/sphere.cpp )

add_executable( torus
                objects/Torus.cpp
                runners/torus.cpp )
target_link_libraries( torus normals )

add_executable( asteroid
                objects/Asteroid.cpp
                runners/asteroid.cpp )

add_executable( sun
                objects/Sphere.cpp
                objects/Sun.cpp
                runners/sun.cpp )

add_executable( rotator
                objects/Rotator.cpp
                runners/rotator.cpp )

add_executable( ship
                objects/Ship.cpp
                runners/ship.cpp )

add_executable( nebula
                objects/Nebula.cpp
                runners/nebula.cpp )
                
add_executable( rectangle
                objects/Rectangle.cpp
                runners/rectangle.cpp )
target_link_libraries( rectangle normals )
                
add_executable( skybox
                util.cpp
                objects/Rectangle.cpp
                objects/Skybox.cpp
                objects/Sun.cpp
                objects/Sphere.cpp
                runners/skybox.cpp )
target_link_libraries( skybox normals )

add_executable( planet
                util.cpp
                objects/Sphere.cpp
                objects/Torus.cpp
                runners/planet.cpp )  
                                                             
add_executable( station
                objects/Chronos.cpp
                runners/station.cpp )

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


foreach( executable project_helix sphere torus asteroid sun rotator ship nebula rectangle skybox planet station)

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
