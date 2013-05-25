#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "objects/Sphere.h"

int main(void) {
	// Sphere(radius, legthSteps, widthSteps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200, 200);
    ref_ptr<Group> root = new Group();

	// giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(sphere.get());

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
