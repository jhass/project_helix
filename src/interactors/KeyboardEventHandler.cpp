#include "KeyboardEventHandler.h"

ph::KeyboardEventHandler::KeyboardEventHandler(View* view) : view(view) {
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
            }
            return true;
        default:
            return false;
    }
}
