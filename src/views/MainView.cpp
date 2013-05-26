#include <osg/Node>
#include <osg/Vec3>

#include "scenes/MainScene.h"

#include "MainView.h"


ph::MainView::MainView() {
    ref_ptr<Node> scene = new ph::MainScene();
    this->setSceneData(scene.get());

    this->getCamera()->setProjectionMatrixAsFrustum(-0.35, 0.35, -0.26, 0.26, 1.0, 10000);
    this->getCamera()->setAllowEventFocus(false);

    this->switchToMainPerspective();
}

void ph::MainView::switchToMainPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(-20, -140, 120), // eye
        Vec3d(0, 0, 0),  // center
        Vec3d(0, 0, 1)   // up
    );
}

void ph::MainView::switchToSecondaryPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(60, 0, 40), // eye
        Vec3d(0, 0, 0),  // center
        Vec3d(0, 0, 1)   // up
    );
}