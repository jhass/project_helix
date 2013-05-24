#ifndef ROTATOR_H
#define ROTATOR_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;
using namespace std;

namespace ph {
    class Rotator : public Geode {
        private:
            double startx;
            double endx;
            ref_ptr<Geometry> rotator;

            void compute();
            void setVerticesAndNormals();
            void setTextureCoordinates(int textureNumber);
            void setIndicies();
          
        public:
            Rotator(const double startx, const double endx);
            ~Rotator();
            void setTexture(const int textureNumber, const string filename);
    };
}

#endif
