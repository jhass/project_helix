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
    /* A nebula/cloud made from a lot of stationary particles */
    class Nebula : public ProxyNode {
    
        private:
            static void createParticles(ref_ptr<ParticleSystem> ps, double innerRadius, double outerRadius);
            static void createRenderingAttributes(ref_ptr<ParticleSystem> ps, string texturePath);
            
        public:
            Nebula(Vec3d location, string texturePath, double innerRadius, double outerRadius);
    };
}
#endif
