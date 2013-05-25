cmake_minimum_required( VERSION 2.6 )

# Nicht hier sondern CMakeLists.txt.local anlegen und dort ändern
#set(GLUT_INCLUDE_DIR /usr/include/)
#set(GLUT_glut_LIBRARY /usr/lib/libglut.so)


if( EXISTS CMakeLists.txt.local )
  include( CMakeLists.txt.local )
endif()

add_library( normals 3rdparty/osgToy/Normals.cpp )
add_subdirectory( src )
