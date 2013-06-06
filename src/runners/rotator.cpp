#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "objects/Rotator.h"

int main(void) {
    ref_ptr<ph::Rotator> rotator = new ph::Rotator(-300, 408, 30);
    ref_ptr<Group> root = new Group();

   // root->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(rotator.get());

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     //pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
