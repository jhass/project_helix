#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "../objects/sun.h"

int main(void) {
    ref_ptr<ph::Sun> sun = new ph::Sun(5, 200, 200,0);
    ref_ptr<Group> sun_Node = new Group();

    //sun->setTexture(0, "../Textures/EarthMap.jpg");
    
    sun_Node->addChild(sun.get());
    sun_Node->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    sun->setLightAndMaterial(sun_Node);
    

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // sun_Node->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(sun_Node.get());
    return viewer.run();
}
