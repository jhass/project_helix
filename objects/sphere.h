#ifndef SPHERE_H
#define SPHERE_H

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

namespace ph {
  class Sphere : public Geode {
    private:
      double radius;
      int lsteps;
      int wsteps;
      Geometry* compute();
    public:
      Sphere(const double radius, const int lsteps, const int wsteps);
  };
}

#endif
