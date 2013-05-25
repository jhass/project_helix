#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "../objects/sphere.h"

int main(void) {
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200, 200);
    ref_ptr<Group> root = new Group();

    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(sphere.get());

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
