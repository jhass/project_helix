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

ph::Comet::Comet(const double radius, const int lsteps, const int wsteps, 
                 const int xd, const int yd, const int zd) {
    asteroid = new Asteroid(radius, lsteps, wsteps, xd, yd, zd);
    asteroid->setTexture(0, "../Textures/phobos.jpg");

    //Moving the origin of particles
    particleSystem = new MatrixTransform();
    particleSystem->setMatrix( Matrix::translate(0, 5, 0) );

    //Creating the particlesystem at the point defined above
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

    // creating animation path for comet
    osg::ref_ptr<osg::AnimationPathCallback> animation_asteroid = new osg::AnimationPathCallback;
    animation_asteroid->setAnimationPath( ph::createAnimationPath(600.0f, 20*PI, ph::LOOP, ph::NEG_X_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y, NULL, 0, z));
    trans_asteroid->setUpdateCallback( animation_asteroid.get() );
    
    
    // Creating Animation; Movement of the particles
    osg::ref_ptr<osg::AnimationPathCallback> animation_particle = new osg::AnimationPathCallback;
    animation_particle->setAnimationPath( ph::createAnimationPath(600.0f, 0, ph::LOOP, ph::NO_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y+5, NULL, 0, z));
    particleSystem->setUpdateCallback( animation_particle.get() );

    this->addChild(trans_asteroid.get());
}

ParticleSystem* ph::Comet::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    Particle* part = new Particle();
    part->setShape(Particle::POINT);
    part->setLifeTime(5);
    ps->setDefaultParticleTemplate(*part);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create texture
    ref_ptr<Texture2D> texture = new Texture2D;

    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
    
    // StateSetattribute setzen
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    // Texture übergeben
    ss->setTextureAttributeAndModes(0, texture.get());
    // Point-Atrribut setzen
    ref_ptr<Point> attribute = new Point(6.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    // Lichteffekte auf Partikel ausmachen
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    // Rendering einstellen
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Rng
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 500, 1000 );
    
    //makeshooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-PI_2+PI_4/2,-PI_2-PI_4/2); // Streuung z-x-ebene gegen UZS
    myshooter->setPhiRange(PI_2-PI_4/2,PI_2+PI_4/2); //Streuung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(5,20); //Geschwindigkeit
    
    //Emmiter
    ref_ptr<ModularEmitter> emitter = new ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
        
    //??
    ref_ptr<ModularProgram> program = new ModularProgram();
    program->setParticleSystem( ps.get() );

    
    //Rendering stuff2
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.release();
}

