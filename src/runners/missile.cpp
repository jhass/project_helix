#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osg/Math>
#include <osg/LightModel>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Point>
#include <osg/PointSprite>
#include <osgGA/StateSetManipulator>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RadialShooter>
#include <osg/BlendFunc>
#include <osgParticle/ParticleSystem>
#include <osgDB/ReadFile>
#include <osg/Texture2D>

#include "objects/Ship.h"
#include "objects/Fins.h"
#include "objects/Rotator.h"
#include "util.h"
#include "objects/Sphere.h"
#include "objects/Missile.h"
using namespace osg;



int main(void) {

    ref_ptr<ph::Missile> missile = new ph::Missile();
    ref_ptr<osg::Group> root = new Group();
    root->addChild(missile.get());

     

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
    // pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());
 
    
     
     
     
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
