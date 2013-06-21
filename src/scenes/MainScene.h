#ifndef PH_MAIN_SCENE_H
#define PH_MAIN_SCENE_H

#include <osg/Group>

#include "objects/Ship.h"
#include <animation/ShipNodeCallback.h>

using namespace osg;

namespace ph {
    class MainScene : public Group {
        public:
            MainScene();
            ref_ptr<ph::Ship> ship;
    };
}

#endif
