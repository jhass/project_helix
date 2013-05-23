#include <osgDB/ReadFile>

#include "ship.h"



string ph::Ship::fileLocation = "../resources/cruiser.obj";

osgParticle::ParticleSystem* ph::Ship::createParticleSystem( osg::Group* parent ) {
    osg::ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem;
    ps->getDefaultParticleTemplate().setShape( osgParticle::Particle::POINT );
    
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
//    texture->setImage( osgDB::readImageFile("../smoke.rgb") );
    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
//    texture->setImage( osgDB::readImageFile("../resources/fireparticle8x8.png") );
    
    osg::StateSet* ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes( blendFunc.get() );
    ss->setTextureAttributeAndModes( 0, texture.get() );
    
    ss->setAttribute( new osg::Point(20.0f) );
    ss->setTextureAttributeAndModes( 0, new osg::PointSprite );
    
    ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
    ss->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    
    osg::ref_ptr<osgParticle::RandomRateCounter> rrc = new osgParticle::RandomRateCounter;
    rrc->setRateRange( 100, 500 );
    
    osg::ref_ptr<osgParticle::RadialShooter> myshooter = new osgParticle::RadialShooter();
    myshooter->setThetaRange(-1.7,-1.4); // Neigung z-x-ebene gegen UZS
    myshooter->setPhiRange(-0.2,0.2); //Neigung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(3,6); //Geschwindigkeit
    
    osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
    
    osg::ref_ptr<osgParticle::AccelOperator> accel = new osgParticle::AccelOperator;
    accel->setAcceleration(osg::Vec3d(0,0,0));
    
    osg::ref_ptr<osgParticle::ModularProgram> program = new osgParticle::ModularProgram;
    program->setParticleSystem( ps.get() );
    program->addOperator( accel.get() );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.get();
}
 
ph::Ship::Ship() {
    this->addChild(osgDB::readNodeFile(fileLocation));
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->setMatrix( osg::Matrix::translate(-1.5f, 0.0f, 0.0f) );
    
    osgParticle::ParticleSystem* ps = createParticleSystem( mt.get() );
    
    osg::ref_ptr<osgParticle::ParticleSystemUpdater> updater =
        new osgParticle::ParticleSystemUpdater;
    updater->addParticleSystem( ps );

    this->addChild( updater.get() );
    this->addChild( mt.get() );
   }
   

