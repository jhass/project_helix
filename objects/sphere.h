#ifndef SPHERE_H
#define SPHERE_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;
using namespace std;

namespace ph {
    class Sphere : public Geode {
        private:
            double radius;
            int lsteps;
            int wsteps;
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
