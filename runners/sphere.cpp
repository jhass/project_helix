#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>

#include "../objects/sphere.h"

int main(void) {
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 100, 100);
    ref_ptr<MatrixTransform> root = new MatrixTransform;
    root->setMatrix(Matrix::rotate(PI_2, Vec3(1, 0, 0)));
    root->addChild(sphere.get());

    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
