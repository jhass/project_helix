project( project_helix )

include_directories( . .. ../build/src )

configure_file(config.h.in config.h)

add_executable( project_helix
                project_helix.cpp

                # views
                views/MainView.cpp
                views/ShipView.cpp
                
                # scenes
                scenes/MainScene.cpp
                
                # basic objects
                objects/Rectangle.cpp
                objects/Sphere.cpp
                objects/Torus.cpp
                objects/Nebula.cpp
                objects/Fins.cpp
                objects/Rotator.cpp
                
                # external objects
                objects/Chronos.cpp
                objects/Ship.cpp 
                objects/Reaper.cpp
                
                # composed objects
                objects/Asteroid.cpp
                objects/AsteroidField.cpp
                objects/Comet.cpp
                objects/PlanetRing.cpp
                objects/Skybox.cpp
                objects/Sun.cpp
                objects/Missile.cpp
                
                # user interaction
                interactors/KeyboardEventHandler.cpp
                animation/ShipNodeCallback.cpp
                animation/MissileNodeCallback.cpp

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
                objects/Fins.cpp
                runners/rotator.cpp
                util.cpp
                objects/Sphere.cpp
                objects/Ship.cpp)
                
add_executable( missile
                objects/Missile.cpp
                objects/Fins.cpp
                objects/Rotator.cpp
                runners/missile.cpp
                util.cpp
                objects/Sphere.cpp
                )
                
add_executable( ship
                objects/Ship.cpp
                animation/ShipNodeCallback.cpp
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
                objects/Ship.cpp
                objects/Chronos.cpp
                objects/Reaper.cpp
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
find_package( osgShadow )
find_package( osgUtil )
find_package( osgViewer )
find_package( GLUT )
find_package( OpenGL )

foreach( executable project_helix sphere torus asteroid sun rotator missile ship nebula rectangle skybox planet station)


  config_project( ${executable} OPENTHREADS )
  config_project( ${executable} OSG )
  config_project( ${executable} OSGGA )
  config_project( ${executable} OSGDB )
  config_project( ${executable} OSGUTIL )
  config_project( ${executable} OSGSHADOW )
  config_project( ${executable} OSGPARTICLE )
  config_project( ${executable} OSGVIEWER )
  config_project( ${executable} GLUT )
  config_project( ${executable} OPENGL )
endforeach()
