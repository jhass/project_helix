#ifndef PH_ASTEROID_H
#define PH_ASTEROID_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;
using namespace std;

namespace ph {
    class Asteroid : public Geode {
        private:
            double radius; // initial radius of sphere
            int lsteps; 
            int wsteps; // steps in length/ width to create the sphere
            int xd; // deformationfactor in x
            int yd; // -"- in y
            int zd; // -"- in z
            ref_ptr<Geometry> asteroid;

            void compute();
            void setCoordinates();
            void setIndicies();
            void setTextureCoordinates(int textureNumber);
          
        public:
            Asteroid(const double radius, const int lsteps, const int wsteps, 
                     const int xd, const int yd, const int zd);
            void setTexture(const int textureNumber, const string filename);
            ~Asteroid();
    };
}

#endif
