#ifndef PH_SHIP_H
#define PH_SHIP_H

#include <string>

#include <osg/Vec3d>
#include <osg/ProxyNode>
#include <osgParticle/ParticleSystem>
#include <osg/MatrixTransform>

using namespace std;
using namespace osg;
using namespace osgParticle;

namespace ph {
    /*A ship loaded from a given model with an exhaust-particlesystem. Can interact with ShipNodeCallback
    to animate the ship. Has a Camera that will follow on animation.*/
    class Ship : public ProxyNode {
        private:
            static string fileLocation;
            static ParticleSystem* createParticleSystem(Group* parent);

        public: 
            Ship();
            // void addNode(Node* node);
            ref_ptr<MatrixTransform> rotate;
            ref_ptr<MatrixTransform> translate;
            ref_ptr<Camera> camera;
    };
}

#endif
