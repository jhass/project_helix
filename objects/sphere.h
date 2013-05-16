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
          ref_ptr<Geometry> sphere;

          void compute();
          void setVerticiesAndNormals();
          void setIndicies();
          
        public:
            Sphere(const double radius, const int lsteps, const int wsteps);
            ~Sphere();
    };
}

#endif
