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
            void setCoordinates();
            void setIndicies();
          
        public:
            Sphere(const double radius, const int lsteps, const int wsteps);
            ~Sphere();
    };
}


class StackedSphere : public Geode {
    public:
        StackedSphere(const double radius, const int stacks, const int slices);
};

#endif
