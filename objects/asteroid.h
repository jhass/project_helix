#ifndef ASTEROID_H
#define ASTEROID_H

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

namespace ph {
    class Asteroid : public Geode {
        private:
            double radius;
            int lsteps;
            int wsteps;
            int xd;
            int yd;
            int zd;
            ref_ptr<Geometry> asteroid;

            void compute();
            void setCoordinates();
            void setIndicies();
          
        public:
            Asteroid(const double radius, const int lsteps, const int wsteps, 
            	   int xd, int yd, int zd);
            ~Asteroid();
    };
}

#endif
