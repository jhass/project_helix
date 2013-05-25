#include "ship.h"

//Define the filelocation of the ship's .obj file here
string ph::Ship::fileLocation = "../resources/cruiser.obj";

//Particle function of DOOM
osgParticle::ParticleSystem* ph::Ship::createParticleSystem( Group* parent ) {
    ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem();
    ps->getDefaultParticleTemplate().setShape( osgParticle::Particle::POINT );
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //choosing the texture, gonna have to create one somtimes soon......
    ref_ptr<Texture2D> texture = new Texture2D;
//    texture->setImage( osgDB::readImageFile("../smoke.rgb") );
    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
//    texture->setImage( osgDB::readImageFile("../resources/fireparticle8x8.png") );
    
    //Rendering stuffsies
    StateSet* ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes( blendFunc.get() );
    ss->setTextureAttributeAndModes( 0, texture.get() );
    ss->setAttribute( new Point(20.0f) );
    ss->setTextureAttributeAndModes( 0, new PointSprite );
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Rng
    ref_ptr<osgParticle::RandomRateCounter> rrc = new osgParticle::RandomRateCounter();
    rrc->setRateRange( 100, 500 );
    
    //makeshooter
    ref_ptr<osgParticle::RadialShooter> myshooter = new osgParticle::RadialShooter();
    myshooter->setThetaRange(-1.7,-1.4); // Neigung z-x-ebene gegen UZS
    myshooter->setPhiRange(-0.2,0.2); //Neigung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(3,6); //Geschwindigkeit
    
    //Emmiter
    ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
    
    //Acceleration operations
    ref_ptr<osgParticle::AccelOperator> accel = new osgParticle::AccelOperator();
    accel->setAcceleration(Vec3d(-10,0,0)); //Bremsvektor
    
    //??
    ref_ptr<osgParticle::ModularProgram> program = new osgParticle::ModularProgram();
    program->setParticleSystem( ps.get() );
    program->addOperator( accel.get() );
    
    //Rendering stuff2
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.get();
}
 
ph::Ship::Ship() {
    //Loading the model of the ship + adding it as a Child
    this->addChild(osgDB::readNodeFile(fileLocation));

    //Moving the origin of particles
    ref_ptr<MatrixTransform> mt = new MatrixTransform();
    mt->setMatrix( Matrix::translate(-1.5f, 0.0f, 0.0f) );

    //Creating the particlesystem at the point defined above
    osgParticle::ParticleSystem* ps = createParticleSystem(mt.get());
    ref_ptr<osgParticle::ParticleSystemUpdater> updater =
        new osgParticle::ParticleSystemUpdater();
    updater->addParticleSystem( ps );

    //Adding particlesystem and updater to ship's node
    this->addChild( updater.get() );
    this->addChild( mt.get() );
   }
   

