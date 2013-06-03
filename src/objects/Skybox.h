#ifndef PH_SKYBOX_H
#define PH_SKYBOX_H

#include <string>

#include <osg/Group>
#include <osg/Geometry>

#include "Rectangle.h"

using namespace std;
using namespace osg;

namespace ph {
    class Skybox : public Group {
        private:
            int height;
            int width;
            // rectangles relative to the center of the skybox
            ref_ptr<Rectangle> front; // rectangle in front of the middle
            ref_ptr<Rectangle> back; // rectangle in back of the middle
            ref_ptr<Rectangle> left; // rectangle left of the middle
            ref_ptr<Rectangle> right; // rectangle right of the middle
            ref_ptr<Rectangle> top; // rectangle over the middle
            ref_ptr<Rectangle> bottom; // rectangle under the middle
            ref_ptr<Group> skybox;
        
        void createRectangles();
        
        public:
           enum Position {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
           Skybox(const int height, const int width);
           void setTexture(const Position pos, const int textureNumber, const string filename);
    };
}
#endif
