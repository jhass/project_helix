#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>

#include "objects/Sun.h"
#include "objects/Sphere.h"

int main(void) {
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun = new ph::Sun(8, 200, 1, 0.9, 0.6, 0.0);
    
    // pushing sun to the left
    ref_ptr<MatrixTransform> suntrans = new MatrixTransform();
    suntrans->setMatrix(Matrix::translate(Vec3d(-20,0,0))); 
    suntrans->addChild(sun.get());
    
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun2 = new ph::Sun(5, 200, 0, 0.9, 0.0, 0.6);
    
    // pushing sun to the left
    ref_ptr<MatrixTransform> suntrans2 = new MatrixTransform();
    suntrans2->setMatrix(Matrix::translate(Vec3d(0,20,0))); 
    suntrans2->addChild(sun2.get());
    
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200);

    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    // pushing sphere to the right
    ref_ptr<MatrixTransform> spheretrans = new MatrixTransform();
    spheretrans->setMatrix(Matrix::translate(Vec3d(20,0,0)));
    spheretrans->addChild(sphere.get());

    ref_ptr<Group> root = new Group();
    root->addChild(suntrans.get());
    root->addChild(suntrans2.get());
    root->addChild(spheretrans.get());

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // sun_Node->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
