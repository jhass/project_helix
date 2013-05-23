#ifndef SHIP_H
#define SHIP_H

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
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgViewer/ViewerEventHandlers>
#include <osgParticle/RadialShooter>


using namespace osg;
using namespace std;

namespace ph {
    class Ship : public ProxyNode {
        private:
            static string fileLocation;
            static osgParticle::ParticleSystem* createParticleSystem(osg::Group* parent);

        public: 
            Ship();
    };
}

#endif
