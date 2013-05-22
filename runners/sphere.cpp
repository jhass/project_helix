#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include "../objects/sphere.h"


int main(void) {
    // ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 100, 100);
    ref_ptr<StackedSphere> sphere = new StackedSphere(5, 100, 100);
    ref_ptr<Group> root = new Group();
    root->addChild(sphere.get());
    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile("../land_shallow_topo_2048.jpg");
    texture->setImage(image);
    // root->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
