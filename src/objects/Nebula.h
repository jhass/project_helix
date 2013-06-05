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
            static void createParticles(ref_ptr<ParticleSystem> ps);
            static void createRenderingAttributes(ref_ptr<ParticleSystem> ps);
            
        public:
            Nebula(Vec3d& location);
    };
}

#endif
