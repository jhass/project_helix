#ifndef PH_FINS_H
#define PH_FINS_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;
using namespace std;

namespace ph {
    class Fins : public Geode {
        private:
            int position;
            int factor;
            ref_ptr<Geometry> fins;

            void compute();
            void setVerticesAndNormals();
            void setTextureCoordinates(int textureNumber);
            void setIndicies();
            void setFins(int factor);
          
        public:
            Fins(const int position, const int factor);
            ~Fins();
            void setTexture(const int textureNumber, const string filename);
    };
}

#endif
