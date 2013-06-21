#ifndef PH_SHIP_NODE_CALLBACK_H
#define PH_SHIP_NODE_CALLBACK_H

#include <osg/NodeCallback>
#include <osg/Vec3d>
#include <osg/Quat>

using namespace osg;

namespace ph {
    /* An UpdateCallback for the ship. Moves the Ship forward and rotates it PI/60 when one of the functions is called.
    Repeats each frame, so a vertical synchronisation is recommended. Turbo increases the speed, doesn't simulate
    acceleration */
    class ShipNodeCallback : public NodeCallback {
        public:
            virtual void operator()(Node* node, NodeVisitor* nv);
            void yawLeft();
            void yawRight();
            void pitchUp();
            void pitchDown();
            void turboOn();
            void turboOff();

        private:
            static Vec3d direction, up, x_axis, y_axis, z_axis;
            static double pitch, yaw, roll, speed;
    };
}
#endif
