#include <osg/Node>
#include <osg/Vec3>
#include <osgGA/NodeTrackerManipulator>

#include "ShipView.h"

using namespace osg;
using namespace osgGA;

ph::ShipView::ShipView(ph::MainScene* _scene) {
    ref_ptr<MainScene> scene = _scene;
    this->setSceneData(scene.get());

    scene->ship->camera = this->getCamera();
    this->getCamera()->setProjectionMatrixAsFrustum(-0.35, 0.35, -0.26, 0.26, 1.0, 10000);
    this->getCamera()->setAllowEventFocus(false);
}
