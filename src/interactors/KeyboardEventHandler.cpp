#include "KeyboardEventHandler.h"

ph::KeyboardEventHandler::KeyboardEventHandler(ph::MainView* view) : view(view) {
    this->view->addEventHandler(this);
}

bool ph::KeyboardEventHandler::handle(const GUIEventAdapter& eventAdapter, GUIActionAdapter& actionAdapter) {
    switch (eventAdapter.getEventType()) {
        case GUIEventAdapter::KEYUP:
            switch (eventAdapter.getKey()) {
                case GUIEventAdapter::KEY_1:
                    this->view->switchToMainPerspective();
                    break;
                case GUIEventAdapter::KEY_2:
                    this->view->switchToSecondPerspective();
                    break;
                case GUIEventAdapter::KEY_3:
                    this->view->switchToThirdPerspective();
                    break;
                case GUIEventAdapter::KEY_A:
                    this->view->yawShipLeft();
                    break;
                case GUIEventAdapter::KEY_D:
                    this->view->yawShipRight();
                    break;
            }
            return true;
        default:
            return false;
    }
}
