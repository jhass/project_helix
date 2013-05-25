#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "../objects/sun.h"

int main(void) {
	// Sun(radius, lengthSteps, widthSteps, GLLightNumber)
    ref_ptr<ph::Sun> sun = new ph::Sun(5, 200, 200,0);
    ref_ptr<Group> sun_Node = new Group();
    
    sun_Node->addChild(sun.get());
    // gives the information for the light to the Node
    sun->setLightAndMaterial(sun_Node);
    

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // sun_Node->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(sun_Node.get());
    return viewer.run();
}
