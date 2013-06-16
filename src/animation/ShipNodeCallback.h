#ifndef SHIP_NODE_CALLBACK
#define SHIP_NODE_CALLBACK

#include <osg/NodeCallback>
#include <osg/Vec3d>
#include <osg/Quat>

#include "objects/Ship.h"

using namespace osg;

namespace ph {
	class ShipNodeCallback : public NodeCallback {
		public:
			virtual void operator()(Node* node, NodeVisitor* nv);
			void yawLeft();
			void yawRight();

		private:
			static Vec3d direction;
			static double pitch, yaw, roll;
	};
}
#endif