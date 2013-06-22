#include <osg/BlendFunc>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Point>
#include <osg/PointSprite>
#include <osgParticle/RadialShooter>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/ParticleSystemUpdater>
#include <osg/AnimationPath>

#include "util.h"

#include "Comet.h"

/* creates a comet using an object from the asteroid-class with a
   particle system as tail*/
ph::Comet::Comet(const double radius, const int lsteps, const int wsteps, 
                 const int xd, const int yd, const int zd) {
    asteroid = new Asteroid(radius, lsteps, wsteps, xd, yd, zd);
    asteroid->setTexture(0, "../Textures/phobos.jpg");

    // moving the origin of particles
    particleSystem = new MatrixTransform();
    particleSystem->setMatrix( Matrix::translate(0, 5, 0) );

    // creating the particlesystem at the point defined above
    ref_ptr<ParticleSystem> ps = createParticleSystem(particleSystem.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);

    this->addChild(particleSystem);
    this->addChild(updater);
}

void ph::Comet::Comet::translateAndAnimate(double x, double y, double z) {
    ref_ptr<MatrixTransform> trans_asteroid = new MatrixTransform;
    trans_asteroid->setMatrix(Matrix::translate(x, y, z));
    trans_asteroid->addChild(asteroid.get());

    double delta_x = 800.0, delta_y = 2000.0;

    // creating animation path for comet; moving and rotation
    osg::ref_ptr<osg::AnimationPathCallback> animation_asteroid = new osg::AnimationPathCallback;
    animation_asteroid->setAnimationPath( ph::createAnimationPath(600.0f, 20*PI, ph::LOOP, ph::NEG_X_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y, NULL, 0, z));
    trans_asteroid->setUpdateCallback( animation_asteroid.get() );
    
    
    // creating animation for particles; moving
    osg::ref_ptr<osg::AnimationPathCallback> animation_particle = new osg::AnimationPathCallback;
    animation_particle->setAnimationPath( ph::createAnimationPath(600.0f, 0, ph::LOOP, ph::NO_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y+5, NULL, 0, z));
    particleSystem->setUpdateCallback( animation_particle.get() );

    this->addChild(trans_asteroid.get());
}

// creates the particle system for the tail
ParticleSystem* ph::Comet::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    
    // particles; type: point, life time: 5 s
    Particle* part = new Particle();
    part->setShape(Particle::POINT);
    part->setLifeTime(5);
    ps->setDefaultParticleTemplate(*part);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // create texture
    ref_ptr<Texture2D> texture = new Texture2D;

    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
    
    // creating stateset
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    
    // adding texture to stateset
    ss->setTextureAttributeAndModes(0, texture.get());
    
    // setting point-attributes
    ref_ptr<Point> attribute = new Point(6.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    
    // switching of light
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    
    // setting rendering
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    // setting ratecounter
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 500, 1000 );
    
    // setting shooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-PI_2+PI_4/2,-PI_2-PI_4/2); // setting x-z-scattering (gg UZS)
    myshooter->setPhiRange(PI_2-PI_4/2,PI_2+PI_4/2); // setting x-y-scattering (gg UZS)
    myshooter->setInitialSpeedRange(5,20); // setting particle speed in range of [5,20]
    
    // setting emitter
    ref_ptr<ModularEmitter> emitter = new ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
        
    // setting modul
    ref_ptr<ModularProgram> program = new ModularProgram();
    program->setParticleSystem( ps.get() );

    
    // adding a required obejcts together
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.release();
}
