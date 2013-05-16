#ifndef SPHERE_H
#define SPHERE_H

#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osg/PolygonMode>
#include <math.h>

using namespace osg;
using namespace std;

Geometry* createSphere(const double radius, const int lsteps, const int wsteps);

#endif
