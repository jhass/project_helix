#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osgGA/StateSetManipulator>
#include "objects/Missile.h"
using namespace osg;



int main(void) {

    ref_ptr<ph::Missile> missile = new ph::Missile();
    ref_ptr<osg::Group> root = new Group();
    root->addChild(missile.get());

     

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
    // pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());
 
    
     
     
     
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
