#ifndef PH_NEBULA_H
#define PH_NEBULA_H

#include <string>

#include <osg/Vec3d>
#include <osg/ProxyNode>
#include <osgParticle/Particle>

using namespace std;
using namespace osg;
using namespace osgParticle;

namespace ph {
    class Nebula : public ProxyNode {
    
        private:
            static string texturePath;
            static Particle* createParticleOnLocation(const Vec3d* location);
            
        public:
            Nebula(Vec3d* location);
    };
}

#endif
