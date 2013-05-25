#include <osg/MatrixTransform>
#include <osg/Point>
#include <osg/PointSprite>
#include <osg/Texture2D>
#include <osg/BlendFunc>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RadialShooter>

#include "Ship.h"

//Define the filelocation of the ship's .obj file here
string ph::Ship::fileLocation = "../resources/cruiser.obj";

//Particle function of DOOM
ParticleSystem* ph::Ship::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    ps->getDefaultParticleTemplate().setShape(Particle::POINT);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //choosing the texture, gonna have to create one somtimes soon......
    ref_ptr<Texture2D> texture = new Texture2D;
//    texture->setImage( osgDB::readImageFile("../smoke.rgb") );
    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
//    texture->setImage( osgDB::readImageFile("../resources/fireparticle8x8.png") );
    
    //Rendering stuffsies
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    ss->setTextureAttributeAndModes(0, texture.get());
    ref_ptr<Point> attribute = new Point(20.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Rng
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 100, 500 );
    
    //makeshooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-1.7,-1.4); // Neigung z-x-ebene gegen UZS
    myshooter->setPhiRange(-0.2,0.2); //Neigung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(3,6); //Geschwindigkeit
    
    //Emmiter
    ref_ptr<ModularEmitter> emitter = new ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
    
    //Acceleration operations
    ref_ptr<AccelOperator> accel = new AccelOperator();
    accel->setAcceleration(Vec3d(-10,0,0)); //Bremsvektor
    
    //??
    ref_ptr<ModularProgram> program = new ModularProgram();
    program->setParticleSystem( ps.get() );
    program->addOperator( accel.get() );
    
    //Rendering stuff2
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.release();
}
 
ph::Ship::Ship() {
    //Loading the model of the ship + adding it as a Child
    this->addChild(osgDB::readNodeFile(fileLocation));

    //Moving the origin of particles
    ref_ptr<MatrixTransform> mt = new MatrixTransform();
    mt->setMatrix( Matrix::translate(-1.5f, 0.0f, 0.0f) );

    //Creating the particlesystem at the point defined above
    ref_ptr<ParticleSystem> ps = createParticleSystem(mt.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);

    //Adding particlesystem and updater to ship's node
    this->addChild(updater.get());
    this->addChild(mt.get());
   }
   

