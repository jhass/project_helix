#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <cmath>
#include "Fins.h"
#include "Rotator.h"
#include "Missile.h"
#include <osg/Geode>
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
using namespace osg;

ParticleSystem* createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    ps->getDefaultParticleTemplate().setShape(Particle::POINT);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Texture erzeugen
    ref_ptr<Texture2D> texture = new Texture2D;

    texture->setImage( osgDB::readImageFile("../resources/particle_2.rgb") );
    
    // StateSetattribute setzen
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    // Texture übergeben
    ss->setTextureAttributeAndModes(0, texture.get());
    // Point-Atrribut setzen
    ref_ptr<Point> attribute = new Point(10.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    // Lichteffekte auf Partikel ausmachen
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    // Rendering einstellen
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Rng
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 50, 500 ); //Anzahl der Partikel/Sekunde
    
    //makeshooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-PI_2-0.05,-PI_2+0.05); // Streuung z-x-ebene gegen UZS
    myshooter->setPhiRange(-0.02,0.02); //Streuung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(0,10); //Geschwindigkeit
    
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


ph::Missile::Missile() {
    ref_ptr<ph::Rotator> rotator = new ph::Rotator(-1.7, 1.81, 30);
    rotator->setTexture(0, "../Textures/rotator_tx.png");
    
    ref_ptr<ph::Fins> fins1a = new ph::Fins(0,0.4);
    fins1a->setTexture(0, "../Textures/fin.png");
    
    osg::ref_ptr<osg::MatrixTransform> transf1a = new osg::MatrixTransform;

 
    transf1a->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(-135.0), 1, 0, 0));
    transf1a->addChild(fins1a.get());
   
    osg::ref_ptr<osg::MatrixTransform> transf1b = new osg::MatrixTransform;
    transf1b->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0), 1, 0, 0));
    transf1b->addChild(fins1a.get());
    
   
    osg::ref_ptr<osg::MatrixTransform> transf1c = new osg::MatrixTransform;
    transf1c->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(135.0), 1, 0, 0));
    transf1c->addChild(fins1a.get());
    
  
    osg::ref_ptr<osg::MatrixTransform> transf1d = new osg::MatrixTransform;
    transf1d->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(-45.0), 1, 0, 0));
    transf1d->addChild(fins1a.get());
    
  
    
    
    ref_ptr<Group> fins1 = new Group();
    fins1->addChild(transf1a.get());
    fins1->addChild(transf1b.get());
    fins1->addChild(transf1c.get());
    fins1->addChild(transf1d.get());

    
    osg::ref_ptr<osg::MatrixTransform> transf = new osg::MatrixTransform;
    transf->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(-0.8f, 0.0f, 0.0f)));
    transf->addChild(fins1.get());
  
    osg::ref_ptr<osg::MatrixTransform> transf2 = new osg::MatrixTransform;
    transf2->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(1.0f, 0.0f, 0.0f)));
    transf2->addChild(fins1.get());
    
  
    ref_ptr<LightModel> lm = new LightModel;
    lm->setTwoSided(true);
    fins1->getOrCreateStateSet()->setAttributeAndModes(lm.get());

    ref_ptr<ph::Sphere> sphere = new ph::Sphere(0.1, 200);
    ref_ptr<Material> material = new Material;
    material->setEmission(Material::FRONT_AND_BACK, Vec4(100,1,50,1.0));
    material->setShininess(Material::FRONT_AND_BACK, 10);
    
    sphere->getOrCreateStateSet()->setAttributeAndModes(material.get(),StateAttribute::ON);
   
   
    
    
    
    ref_ptr<MatrixTransform> planet = new MatrixTransform;
    
    planet->setMatrix(Matrix::translate(-1.8,0.0,0.0));
    sphere->setTexture(0,"../Textures/rocketeng.jpeg"); //mit durch Material ergänzen
    planet->addChild(sphere.get());
    
    //Partikelsystem start
    
       ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
     //Creating the particlesystem at the point defined above
    
    ref_ptr<osg::MatrixTransform> mtx = new osg::MatrixTransform;
    mtx->setMatrix(Matrix::translate(-5.0,0.0,0.0));  //um 5 ans Heck der Missile verschieben
    
    ref_ptr<ParticleSystem> ps = createParticleSystem(root.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);
   
   
    
    ref_ptr<Group> node = new Group();
    node->addChild(updater.get());
    node->addChild(mtx.get());
    
    //PS ende
    
 
  //  root->setMatrix(Matrix::rotate(PI_4,1,0,0));
    root->addChild(rotator.get());
    root->addChild(transf.get());
    root->addChild(transf2.get());
    root->addChild(planet.get());
    root->addChild(node.get());
   
    this->addChild(root.get());
    
    
    
    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath( ph::createAnimationPath(10.0f, 2*PI, ph::LOOP, ph::NEG_Z_AXIS,
    ph::sin_f, 20,0 ,ph::cos_f, 20,0, ph::lin_f, -00,0));
    root->setUpdateCallback( apcb.get() );


    
    
   
   
   

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
    // pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());
 
    
     
     
}

    ph::Missile::~Missile() {
    this->missile.release();
}


