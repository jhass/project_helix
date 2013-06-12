#ifndef PH_ROTATOR_H
#define PH_ROTATOR_H

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
            int schritte;
            ref_ptr<Geometry> rotator;

            void compute();
            void setVerticesAndNormals();
            void setTextureCoordinates(int textureNumber);
            void setIndicies();
          
        public:
            Rotator(const int startx, const int endx, const int schritte);
            ~Rotator();
            void setTexture(const int textureNumber, const string filename);
    };
}

#endif
