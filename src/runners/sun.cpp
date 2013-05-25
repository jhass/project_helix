#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>

#include "objects/Sun.h"
#include "objects/Sphere.h"

int main(void) {
	// Sun(radius, lengthSteps, widthSteps, GLLightNumber)
    ref_ptr<ph::Sun> sun = new ph::Sun(5, 200, 200,0);
    ref_ptr<Group> sun_Node = new Group();
    
    sun_Node->addChild(sun.get());
    // gives the information for the light to the Node
    sun->setLightAndMaterial(sun_Node);
    
    // pushing sun to the left
    ref_ptr<MatrixTransform> suntrans = new MatrixTransform();
    suntrans->setMatrix(Matrix::translate(Vec3d(-20,0,0))); 
    suntrans->addChild(sun_Node.get());
    
    // Sphere(radius, legthSteps, widthSteps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200, 200);
    ref_ptr<Group> sphere_Node = new Group();

	// giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    sphere_Node->addChild(sphere.get());
    
    // pushing sphere to the right
    ref_ptr<MatrixTransform> spheretrans = new MatrixTransform();
    spheretrans->setMatrix(Matrix::translate(Vec3d(20,0,0)));
    spheretrans->addChild(sphere_Node.get());

	ref_ptr<Group> root = new Group();
	root->addChild(suntrans.get());
	root->addChild(spheretrans.get());

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // sun_Node->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
