#include "KeyboardEventHandler.h"

ph::KeyboardEventHandler::KeyboardEventHandler(ph::MainView* view) : view(view) {}

bool ph::KeyboardEventHandler::handle(const GUIEventAdapter& eventAdapter, GUIActionAdapter& actionAdapter) {
    switch (eventAdapter.getEventType()) {
        case GUIEventAdapter::KEYDOWN:
            switch (eventAdapter.getKey()) {
                case '1':
                    this->view->switchToMainPerspective();
                    break;
                case '2':
                    this->view->switchToSecondPerspective();
                    break;
                case '3':
                    this->view->switchToThirdPerspective();
                    break;
                case 'A':
                case 'a':
                    this->view->yawShipLeft();
                    break;
                case 'D':
                case 'd':
                    this->view->yawShipRight();
                    break;
                case 'W':
                case 'w':
                    this->view->pitchShipDown();
                    break;
                case 'S':
                case 's':
                    this->view->pitchShipUp();
                    break;
                case 'Q':
                case 'q':
                    this->view->rollShipLeft();
                    break;
                case 'E':
                case 'e':
                    this->view->rollShipRight();
                    break;
                case GUIEventAdapter::KEY_Shift_L:
                    this->view->shipTurboOn();
                    break;
            }
            return true;
        case GUIEventAdapter::KEYUP:
            switch (eventAdapter.getKey()) {
                case GUIEventAdapter::KEY_Shift_L:
                    this->view->shipTurboOff();
                    break;
            }
            return true;
        default:
            return false;
    }
}
