#include <osg/Node>
#include <osg/Vec3>

#include "scenes/MainScene.h"

#include "CockpitView.h"

using namespace osg;

ph::CockpitView::CockpitView() {
    ref_ptr<Node> scene = new ph::MainScene();
    this->setSceneData(scene.get());

    this->getCamera()->setProjectionMatrixAsFrustum(-0.35, 0.35, -0.26, 0.26, 1.0, 10000);
    this->getCamera()->setAllowEventFocus(false);
    // TODO: update with animation, possibly some callback mechanism
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(3.5, 0, 1), // eye
        Vec3d(4, 0, 1),  // center
        Vec3d(0, 0, 1)   // up
    );
}
