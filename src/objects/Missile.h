#ifndef PH_MISSILE_H
#define PH_MISSILE_H

#include <string>

#include <osg/Group>
#include <osg/Node>

#include "animation/MissileNodeCallback.h"

using namespace osg;


namespace ph {
    
	class Missile : public Group {        
        public:
            Missile();
            long lifetime;
            ref_ptr<MatrixTransform> rotate;
            ref_ptr<MatrixTransform> translate;
            ref_ptr<ph::MissileNodeCallback> callback;
    };
}

#endif
