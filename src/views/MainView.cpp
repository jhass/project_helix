#include <osg/Node>
#include <osg/Vec3>

#include "MainView.h"

using namespace osg;

ph::MainView::MainView() {
    scene = new ph::MainScene();
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

void ph::MainView::switchToSecondPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(60, 0, 40), // eye
        Vec3d(0, 0, 0),  // center
        Vec3d(0, 0, 1)   // up
    );
}


void ph::MainView::switchToThirdPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(-60, 0, -20), // eye
        Vec3d(0, 0, 0),  // center
        Vec3d(0, 0, 1)   // up
    );   
}


void ph::MainView::yawShipLeft() {
    scene->ship_callback->yawLeft();
}

void ph::MainView::yawShipRight() {
    scene->ship_callback->yawRight();   
}
