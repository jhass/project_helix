#ifndef PH_SKYBOX_H
#define PH_SKYBOX_H

#include <string>

#include <osg/Group>
#include <osg/Geometry>
#include <osg/Depth>
#include <osgUtil/CullVisitor>
#include <osg/MatrixTransform>

#include "Rectangle.h"

using namespace std;
using namespace osg;

namespace ph {
    class Skybox : public Transform {
        private:
            int height;
            int width;
            // rectangles relative to the center of the skybox
            ref_ptr<Rectangle> front; // rectangle in front of the middle (0.0, y, 0.0)
            ref_ptr<Rectangle> back; // rectangle in back of the middle (0.0, -y, 0.0)
            ref_ptr<Rectangle> left; // rectangle left of the middle (-x, 0.0, 0.0)
            ref_ptr<Rectangle> right; // rectangle right of the middle (x, 0.0, 0.0)
            ref_ptr<Rectangle> top; // rectangle over the middle (0.0, 0.0, z)
            ref_ptr<Rectangle> bottom; // rectangle under the middle (0.0, 0.0, -z)
            ref_ptr<Group> skybox;
        
            void createRectangles();
        
        public:
           enum Position {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
           Skybox(const int height, const int width);
           void setTexture(const Position pos, const int textureNumber, const string filename);
           void clampObjectToSkybox(ref_ptr<MatrixTransform>& mt);
           
           // aus: OSG Cookbook, pp. 256ff, Funktionen für Funktionalität: Verschieben der Skybox 
           virtual bool computeLocalToWorldMatrix( osg::Matrix& matrix, osg::NodeVisitor* nv ) const;
           virtual bool computeWorldToLocalMatrix( osg::Matrix& matrix, osg::NodeVisitor* nv ) const;
    };
}
#endif
