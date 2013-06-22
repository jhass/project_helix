#ifndef PH_SHIP_NODE_CALLBACK_H
#define PH_SHIP_NODE_CALLBACK_H

#include <osg/NodeCallback>
#include <osg/Vec3d>

using namespace osg;

namespace ph {
    /* An UpdateCallback for the ship. Moves the Ship forward and rotates it PI/60 when one of the functions is called.
    Repeats each frame, so a vertical synchronisation is recommended. Turbo increases the speed, doesn't simulate
    acceleration */
    class ShipNodeCallback : public NodeCallback {
        public:
            ShipNodeCallback();
            virtual void operator()(Node* node, NodeVisitor* nv);
            void yawLeft();
            void yawRight();
            void pitchUp();
            void pitchDown();
            void rollRight();
            void rollLeft();
            void turboOn();
            void turboOff();
            void fireMissile();

        private:
            Vec3d direction, up, x_axis, y_axis, z_axis;
            double pitch, yaw, roll, speed;
            bool missilefired;
            int missileLifetime;
    };
}
#endif
