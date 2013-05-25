#ifndef PH_KEYBOARD_EVENT_HANDLER_H
#define PH_KEYBOARD_EVENT_HANDLER_H

#include <osgGA/GUIEventHandler>

#include "views/View.h"

using namespace osg;
using namespace osgGA;

namespace ph {
    class KeyboardEventHandler : public GUIEventHandler {
        private:
            ref_ptr<ph::View> view;
        public:
            KeyboardEventHandler(View* view);
            virtual bool handle(const GUIEventAdapter& eventAdapter, GUIActionAdapter& actionAdapter);
    };
}

#endif
