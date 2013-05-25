#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>

#include "../objects/asteroid.h"


int main(void) {
	// Asteroid(radius, lengthSteps, widthSteps, deformationfactor in x,y,z
    ref_ptr<ph::Asteroid> asteroid = new ph::Asteroid(5, 20, 20, 2, 1, 3);
    ref_ptr<Group> root = new Group();
    
    // giving the asteroid a texture
    asteroid->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(asteroid.get());

    // enables PolygonMode
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
