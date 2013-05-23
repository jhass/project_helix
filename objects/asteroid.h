#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;
using namespace std;

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
            void setTextureCoordinates(int textureNumber);
          
        public:
            Asteroid(const double radius, const int lsteps, const int wsteps, 
                     const int xd, const int yd, const int zd);
            void setTexture(const int textureNumber, const string filename);
            ~Asteroid();
    };
}

#endif
