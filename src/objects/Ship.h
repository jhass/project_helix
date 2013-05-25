#ifndef PH_SHIP_H
#define PH_SHIP_H

#include <string>

#include <osg/Vec3d>
#include <osg/ProxyNode>
#include <osgParticle/ParticleSystem>

using namespace std;
using namespace osg;
using namespace osgParticle;

namespace ph {
    class Ship : public ProxyNode {
        private:
            static string fileLocation;
            static osgParticle::ParticleSystem* createParticleSystem(Group* parent);

        public: 
            Ship();
    };
}

#endif
