#include <cmath>
#include <osg/MatrixTransform>
#include <osg/Point>
#include <osg/PointSprite>
#include <osg/Texture2D>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>

#include "Nebula.h"

string ph::Nebula::texturePath = "../resources/nebulainner.png";

void ph::Nebula::createRenderingAttributes(ref_ptr<ParticleSystem> ps) {
    //Creating the Blendfunction, whatever that may be.
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //choosing the texture, gonna have to create one somtimes soon......
    ref_ptr<Texture2D> texture = new Texture2D();
    texture->setImage(osgDB::readImageFile(texturePath));

    ref_ptr<StateSet> ss = ps->getOrCreateStateSet(); //Adding it to the Particlsystem here!
    ss->setAttributeAndModes(blendFunc.get());
    ss->setTextureAttributeAndModes(0, texture.get());
    ref_ptr<Point> attribute = new Point(20.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite();
    ss->setTextureAttributeAndModes(0, sprite);
    ss->setMode(GL_LIGHTING, StateAttribute::OFF);
    ss->setRenderingHint(StateSet::TRANSPARENT_BIN);
}

void ph::Nebula::createParticles(ref_ptr<ParticleSystem> ps) {
    Particle particle_template;
    particle_template.setShape(Particle::POINT);
    particle_template.setLifeTime(-1); //Never gets lifelong warranty.......

    double theta, phi;
    double xd = 1;
    double yd = 1;  //Setting Dimensions
    double zd = 1;
    double radius = 25;

    for (double r = 2; r < radius; r = r + (pow(r,-2) + 2) ) {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= r; j++) {
                theta = i * PI / r;
                phi = j * 2 * PI / (r-1);
                double random = rand() % 100;
                double nradius = r + (random) * r/100;
                particle_template.setPosition(Vec3d(
                    (rand()%(int)(radius/4))+(xd*nradius*cos(phi)*sin(theta)), 
                    (rand()%(int)(radius/4))+(yd*nradius*sin(phi)*sin(theta)), 
                    (rand()%(int)(radius/4))+(zd*nradius*cos(theta))
                ));
                ps->createParticle(&particle_template);
            }
        }
    }
}


ph::Nebula::Nebula(Vec3d& location) {
    //Set the location of the Nebula
    ref_ptr<MatrixTransform> origin = new MatrixTransform();
    origin->setMatrix(Matrix::translate(location));

    //Creating a container for the ParticleSystem
    ref_ptr<Geode> particlesystemContainer = new Geode();

    //Creating the updater for the ParticleSystem
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    
    //Creating the Particlesystem
    ref_ptr<ParticleSystem> ps = new ParticleSystem();

    //Set the default template of the particles
    ps->getDefaultParticleTemplate().setShape(Particle::POINT);
    ps->getDefaultParticleTemplate().setLifeTime(-1);
    
    //Set the rendering attributes
    createRenderingAttributes(ps);

    //Glueing everything together, needs more Ducttape!
    updater->addParticleSystem(ps.get());
    particlesystemContainer->addDrawable(ps.get());
    origin->addChild(particlesystemContainer.get());

    //Creating a Particle
    ps->createParticle(NULL);

    //Creating loads of Particles (Code secretly stolen from asteroid.cpp)
    createParticles(ps);

    origin->addChild(updater.get());
    this->addChild(origin.get());
}
