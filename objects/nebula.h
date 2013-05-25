#ifndef NEBULA_H
#define NEBULA_H

#include <string>

#include <osg/Vec3d>
#include <osg/ProxyNode>
#include <osg/MatrixTransform>
#include <osg/Point>
#include <osg/PointSprite>
#include <osg/Texture2D>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osgParticle/Particle>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>


using namespace std;
using namespace osg;

namespace ph {
    class Nebula : public ProxyNode {
    
        private:
            static string texturePath;
            static osgParticle::Particle* createParticleOnLocation(const Vec3d* location);
            
        public:
            Nebula(Vec3d* location);
    };
}

#endif
