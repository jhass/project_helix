#ifndef PH_MISSILE_NODE_CALLBACK_H
#define PH_MISSILE_NODE_CALLBACK_H

#include <osg/NodeCallback>
#include <osg/Vec3d>

using namespace osg;

namespace ph {
    /* An UpdateCallback for the Missile. Moves the Missile in the given direction with the given speed. */
    class MissileNodeCallback : public NodeCallback {
        public:
            MissileNodeCallback(Vec3d& _direction, double _speed);
            virtual void operator()(Node* node, NodeVisitor* nv);
        private:
            Vec3d direction;
            double speed;
    };
}
#endif
