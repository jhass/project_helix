#include <cmath>

#include <osg/Matrix>
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
#include "Missile.h"
#include "animation/MissileNodeCallback.h"

//Define the filelocation of the ship's .obj file here
string ph::Ship::fileLocation = "../resources/cruiser.obj";

//Creating a Particlesystem at thegiven location
ParticleSystem* ph::Ship::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    ps->getDefaultParticleTemplate().setShape(Particle::POINT);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Setting the texture
    ref_ptr<Texture2D> texture = new Texture2D;
    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
    
    //Rendering attributes
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    ss->setTextureAttributeAndModes(0, texture.get());
    ref_ptr<Point> attribute = new Point(3.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Create a RandomRateCounter so the amount of particles emmited varies
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 100, 500 );
    
    //Create a ParticleShooter that sets the proper vector in the particles
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-1.7,-1.4); // Neigung z-x-ebene gegen UZS
    myshooter->setPhiRange(-0.2,0.2); //Neigung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(5,15); //Geschwindigkeit
    
    //Create an Emmiter, which is a container for the Shooter, the Counter and the Particlesystem
    ref_ptr<ModularEmitter> emitter = new ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
        
    //Create another container, which contains the Emmitter and Updateallbacks
    ref_ptr<ModularProgram> program = new ModularProgram();
    program->setParticleSystem( ps.get() );

    
    //Adding the Particlesystem to a Geode so it will be drawn
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );

    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.release();
}
 
ph::Ship::Ship() {

    //Set the transformations up for animation
    rotate = new MatrixTransform();
    rotate->setMatrix(Matrix::rotate(0,Vec3d(0,0,0)));
    translate = new MatrixTransform();
    translate->setMatrix(Matrix::translate(Vec3d(0,0,0)));

    translate->addChild(rotate.get());

    //Loading the model of the ship + adding it as a Child
    rotate->addChild(osgDB::readNodeFile(fileLocation));

    //Moving the origin of particles
    ref_ptr<MatrixTransform> mt = new MatrixTransform();
    mt->setMatrix( Matrix::translate(-1.5f, 0.0f, 0.0f) );

    //Creating the particlesystem at the point defined above
    ref_ptr<ParticleSystem> ps = createParticleSystem(mt.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);

    //Adding particlesystem and updater to ship's node
    rotate->addChild(updater.get());
    rotate->addChild(mt.get());

    this->addChild(translate.get());

    //Setting up the Camera
    camera = new Camera();

    // Setup animation callback
    callback = new ShipNodeCallback();
    this->setUpdateCallback(callback.get());

    missiles = list< ref_ptr<Missile> >();

}

void ph::Ship::fireMissile(Vec3d& up, Vec3d& direction, double speed) {
    ref_ptr<Missile> missile = new Missile();
    missile->lifetime = 10*60; //10 seconds * 60 frames
    missile->translate->setMatrix(Matrix::translate(this->translate->getMatrix().getTrans()-up));
    missile->rotate->setMatrix(this->rotate->getMatrix());

    ref_ptr<MissileNodeCallback> mcb = new MissileNodeCallback(direction, speed);
    missile->setUpdateCallback(mcb);

    missiles.push_back(missile);

    this->addChild(missile);
}
