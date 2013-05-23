#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>

#include "../objects/sphere.h"


int main(void) {
    //ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 10, 10);
    ref_ptr<StackedSphere> sphere = new StackedSphere(5, 200, 200);
    ref_ptr<Group> root = new Group();
    
    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile("../Textures/EarthMap.jpg");
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP);
    texture->setImage(image.get());
    root->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    
    root->addChild(sphere.get());

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     //root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
