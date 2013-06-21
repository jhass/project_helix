#include <osg/Node>
#include <osg/Vec3>

#include "scenes/ShadowedScene.h"

#include "config.h"

#include "MainView.h"

using namespace osg;


ph::MainView::MainView() {
    scene = new ph::ShadowedScene();
    
    #ifdef DISABLE_SHADOWS
    scene = new ph::MainScene();
    #endif

    this->setSceneData(scene.get());

    this->getCamera()->setProjectionMatrixAsFrustum(-0.35, 0.35, -0.26, 0.26, 1.0, 10000);
    this->getCamera()->setAllowEventFocus(false);

    this->switchToMainPerspective();
}

ph::MainScene* ph::MainView::getScene() {
    return scene.get();
}

void ph::MainView::switchToMainPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(-800, -1000, 300), // eye
        Vec3d(200, -200, 0),  // center
        Vec3d(0, 0, 1)   // up
    );
}

void ph::MainView::switchToSecondPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(-60, -120, 100), // eye
        Vec3d(-20, 80, 100),  // center
        Vec3d(1, 0, 1)   // up
    );
}


void ph::MainView::switchToThirdPerspective() {
    this->getCamera()->setViewMatrixAsLookAt(
        Vec3d(600, 1000, 200), // eye
        Vec3d(600, 0, 0),  // center
        Vec3d(0, 0, 1)   // up
    );   
}


void ph::MainView::yawShipLeft() {
    scene->ship->callback->yawLeft();
}

void ph::MainView::yawShipRight() {
    scene->ship->callback->yawRight();   
}

void ph::MainView::pitchShipUp() {
    scene->ship->callback->pitchUp();
}

void ph::MainView::pitchShipDown() {
    scene->ship->callback->pitchDown();
}

void ph::MainView::rollShipRight() {
    scene->ship->callback->rollRight();
}
void ph::MainView::rollShipLeft() {
    scene->ship->callback->rollLeft();
}

void ph::MainView::shipTurboOn() {
    scene->ship->callback->turboOn();
}

void ph::MainView::shipTurboOff() {
    scene->ship->callback->turboOff();
}
