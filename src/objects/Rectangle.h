#ifndef PH_RECTANGLE_H
#define PH_RECTANGLE_H

#include <string>

#include <osg/Geode>
#include <osg/Geometry>

using namespace std;
using namespace osg;

namespace ph {
    class Rectangle : public Geode {
        private:
            int height;
            int width;
            ref_ptr<Geometry> rectangle;
            
            void compute();
            void setTextureCoordinates(int textureNumber);
            
        public:
            Rectangle(const int height, const int width);
            void setTexture(const int textureNumber, const string filename);
    };
}
#endif    
