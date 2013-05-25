#ifndef PH_SPHERE_H
#define PH_SPHERE_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace std;
using namespace osg;

namespace ph {
    class Sphere : public Geode {
        private:
            double radius; // radius of the sphere
            int lsteps;
            int wsteps; // steps in length/ width to create the sphere
            ref_ptr<Geometry> sphere;

            void compute();
            void setVerticesAndNormals();
            void setTextureCoordinates(int textureNumber);
            void setIndicies();
          
        public:
            Sphere(const double radius, const int lsteps, const int wsteps);
            ~Sphere();
            void setTexture(const int textureNumber, const string filename);
    };
}

#endif
