#include "nebula.h"

string ph::Nebula::texturePath = "../resources/particle.rgb";

//Create a Particle on the given Location, duh.....
osgParticle::Particle* ph::Nebula::createParticleOnLocation(const Vec3d* location) {
	osgParticle::Particle* p = new osgParticle::Particle();
	p->setShape(osgParticle::Particle::POINT);
    p->setPosition(*location);
    p->setLifeTime(-1); //Never gets lifelong warranty.......
    return p;
}

ph::Nebula::Nebula(Vec3d* location) {
	//Set the location of the Nebula
	ref_ptr<MatrixTransform> origin = new MatrixTransform();
    origin->setMatrix(Matrix::translate(*location));

    //Creating a container for the ParticleSystem
    ref_ptr<Geode> particlesystemContainer = new Geode();

    //Creating the updater for the ParticleSystem
    ref_ptr<osgParticle::ParticleSystemUpdater> updater =
        				new osgParticle::ParticleSystemUpdater();
    
    //Creating the Particlesystem
    ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem();

    //Set the default template of the particles
    ps->getDefaultParticleTemplate().setShape(osgParticle::Particle::POINT);
    ps->getDefaultParticleTemplate().setPosition(*location);
    ps->getDefaultParticleTemplate().setLifeTime(-1);
    
    //Creating the Blendfunction, whatever that may be.
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //choosing the texture, gonna have to create one somtimes soon......
    ref_ptr<Texture2D> texture = new Texture2D();
    texture->setImage(osgDB::readImageFile(texturePath));
    
    //Creating the StateSet for Rendering
    StateSet* ss = ps->getOrCreateStateSet(); //Adding it to the Particlsystem here!
    ss->setAttributeAndModes(blendFunc.get());
    ss->setTextureAttributeAndModes(0, texture.get());
    ss->setAttribute(new Point(20.0f));
    ss->setTextureAttributeAndModes(0, new PointSprite());
    ss->setMode(GL_LIGHTING, StateAttribute::OFF);
    ss->setRenderingHint(StateSet::TRANSPARENT_BIN);

    //Glueing everything together, needs more Ducttape!
    updater->addParticleSystem(ps.get());
    particlesystemContainer->addDrawable(ps.get());
    origin->addChild(particlesystemContainer.get());

    //Creating a Particle
    ps->createParticle(NULL);

	//Creating loads of Particles (Code secretly stolen from asteroid.cpp)   
    Vec3d* coords; // current vertex coordinates
    srand( time(NULL) );
    double theta, phi;
    double xd = 1;
	double yd = 1;	//Setting Dimensions
	double zd = 1;
	double radius = 50;

	for (int r = 1; r <= radius; r += 1) {
    	for (int i = 0; i <= r; i++) {
        	for (int j = 0; j < r; j++) {
        	    theta = i * PI / r;
        	    phi = j * 2 * PI / (r-1);
        	    double random = rand() % 100;
				double nradius = r + (random) * r/100;
        	    coords = new Vec3d(
        	        xd*nradius * cos(phi) * sin(theta), 
        	        yd*nradius * sin(phi) * sin(theta), 
    	            zd*nradius * cos(theta)
	            );
            	ps->createParticle(createParticleOnLocation(coords));
        	}
    	}
	}

    this->addChild(origin.get());
    this->addChild(updater.get()); 
}