#ifndef PH_MAIN_SCENE_H
#define PH_MAIN_SCENE

#include <osg/Group>

#include <animation/ShipNodeCallback.h>

using namespace osg;

namespace ph {
    class MainScene : public Group {
        public:
            MainScene();
            ref_ptr<ph::ShipNodeCallback> ship_callback;
    };
}

#endif
