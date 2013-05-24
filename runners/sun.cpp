#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "../objects/sun.h"

int main(void) {
    ref_ptr<ph::Sun> sun = new ph::Sun(5, 200, 200,1);
    ref_ptr<Group> root = new Group();

    //sun->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(sun.get());
    root->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    sun->setLight(root);
    

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
