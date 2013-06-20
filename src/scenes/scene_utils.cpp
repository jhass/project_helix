#include <osg/MatrixTransform>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Material>
#include <osg/Point>
#include <osg/PointSprite>
#include <osgGA/StateSetManipulator>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RadialShooter>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>

#include "util.h"
#include "scene_utils.h"
#include "objects/Skybox.h"
#include "objects/Sun.h"
#include "objects/Torus.h"
#include "objects/Ship.h"
#include "objects/Chronos.h"
#include "objects/Reaper.h"
#include "objects/Asteroid.h"

// Creating Skybox with Texture and two suns clamped to the skybox
ph::Skybox* ph::createSkybox(int skybox_height, int skybox_width) {

    // ref-Pointer anlegen
	ref_ptr<ph::Skybox> skybox = new ph::Skybox(skybox_height,skybox_width);

	// Texturen für die Rechtecke festlegen
	skybox->setTexture(ph::Skybox::FRONT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::BACK,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::LEFT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::RIGHT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::TOP,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::BOTTOM,0,"../resources/skybox.jpg");
	
	// Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun_orange = new ph::Sun(100.0, 200, 0, 0.9, 0.6, 0.0);
    
    // translating sun and adding it so skybox
    ref_ptr<MatrixTransform> suntrans_or = new MatrixTransform();
    suntrans_or->setMatrix(Matrix::translate(Vec3(800,skybox_width,0)));
    skybox->clampObjectToSkybox(suntrans_or);
    suntrans_or->addChild(sun_orange.get());
    
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun_violet = new ph::Sun(50.0, 200, 0, 0.9, 0.0, 0.6);
    
    // translating sun and adding it so skybox
    ref_ptr<MatrixTransform> suntrans_vl = new MatrixTransform();
    suntrans_vl->setMatrix(Matrix::translate(Vec3(skybox_height,800,0)));
    skybox->clampObjectToSkybox(suntrans_vl);
    suntrans_vl->addChild(sun_violet.get());
    
    return skybox.release();
}

// Creating a planet with given texture
MatrixTransform* ph::createPlanet(double x, double y, double z) {
    ref_ptr<MatrixTransform> planet = new MatrixTransform;
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(500, 200);
    
    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    // Torus(innerRadius, torusRadius, lengthSteps, widthSteps)
    ref_ptr<ph::Torus> torus = new ph::Torus(650, 75, 100);

    // NORMAL is Default
    torus->setStyle(ph::Torus::FLAT);
    torus->setStateSet(ph::createTorusTexture(torus));
       
    planet->setMatrix( Matrix::translate(x, y, z));
    planet->addChild( sphere.get());
    planet->addChild(torus.get());
    
    // Creating Animation; Rotation of the planet
    osg::ref_ptr<osg::AnimationPathCallback> animation_planet = new osg::AnimationPathCallback;
    animation_planet->setAnimationPath( ph::createAnimationPath(600.0f, 2*PI, ph::LOOP, ph::POS_Z_AXIS,
     NULL, 0, x, NULL, 0, y, NULL, 0, z));
    planet->setUpdateCallback( animation_planet.get() );
    
    return planet.release();
}

// Creating a ship specified with type and position(x,y,z)
MatrixTransform* ph::createShip(ph::ShipType type, double x, double y, double z) {
    
    ref_ptr<MatrixTransform> trans_ship = new MatrixTransform;
    trans_ship->setMatrix( Matrix::translate(x, y, z));
    
    switch (type) {
    case TURIAN: trans_ship->addChild(new ph::Ship); break;
    case STATION: trans_ship->addChild(new ph::Chronos); break;
    case REAPER: trans_ship->addChild(new ph::Reaper); break;
    }
    
    return trans_ship.release();
}

// Creating an asteroid field
Group* ph::createAsteroidField() {
    ref_ptr<Group> trans_field = new Group;
    
    // asteroid_standard(radius, lengthSteps, widthSteps, deformationfactor in x,y,z)
    // Big main asteroids
    ref_ptr<ph::Asteroid> asteroid_main_fine = new ph::Asteroid(12, 20, 20, 1, 1, 1);
    
    // getting the big asteroids to its place
    ref_ptr<MatrixTransform> trans_main_01 = new MatrixTransform;
    trans_main_01->setMatrix(Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(55.0, -30.0, -3.0));
    trans_main_01->addChild(asteroid_main_fine.get());
    
    // giving the big asteroids to root
    trans_field->addChild(asteroid_main_fine.get());
    trans_field->addChild(trans_main_01.get());
    
    // small asteroids
    ref_ptr<ph::Asteroid> asteroid_small_crude = new ph::Asteroid(3, 5, 5, 1, 1, 1);
    ref_ptr<ph::Asteroid> asteroid_small_fine = new ph::Asteroid(3, 20, 20, 1, 1, 1);
    
    // getting the small asteroids to its place
    ref_ptr<MatrixTransform> trans_small_01 = new MatrixTransform;
    trans_small_01->setMatrix(Matrix::translate(-5.0, 20.0, 7.0));
    trans_small_01->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_02 = new MatrixTransform;
    trans_small_02->setMatrix(Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(30.0, -3.0, 7.0));
    trans_small_02->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_03 = new MatrixTransform;
    trans_small_03->setMatrix(Matrix::rotate(PI_2,Vec3(1.0,0.0,1.0))*Matrix::translate(35.0, 3.0, 2.0));
    trans_small_03->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_04 = new MatrixTransform;
    trans_small_04->setMatrix(Matrix::translate(31.0, 12.0, 3.0));
    trans_small_04->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_05 = new MatrixTransform;
    trans_small_05->setMatrix(Matrix::translate(31.0, 14.0, 3.0));
    trans_small_05->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_06 = new MatrixTransform;
    trans_small_06->setMatrix(Matrix::translate(7.0, 22.0, -4.0));
    trans_small_06->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_07 = new MatrixTransform;
    trans_small_07->setMatrix(Matrix::translate(-5.0, -25.0, -4.0));
    trans_small_07->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_08 = new MatrixTransform;
    trans_small_08->setMatrix(Matrix::translate(80, -6.0, 16.0));
    trans_small_08->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_09 = new MatrixTransform;
    trans_small_09->setMatrix(Matrix::translate(72, -16.0, 10.0));
    trans_small_09->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_10 = new MatrixTransform;
    trans_small_10->setMatrix(Matrix::translate(60.0, 13.0, -12.0));
    trans_small_10->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_11 = new MatrixTransform;
    trans_small_11->setMatrix(Matrix::translate(28.0, -17.0, 5.0));
    trans_small_11->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_12 = new MatrixTransform;
    trans_small_12->setMatrix(Matrix::translate(20.0, -20.0, 0.0));
    trans_small_12->addChild(asteroid_small_crude.get());
    
    // giving the small astroids to root
    trans_field->addChild(trans_small_01.get());
    trans_field->addChild(trans_small_02.get());
    trans_field->addChild(trans_small_03.get());
    trans_field->addChild(trans_small_04.get());
    trans_field->addChild(trans_small_05.get());
    trans_field->addChild(trans_small_06.get());
    trans_field->addChild(trans_small_07.get());
    trans_field->addChild(trans_small_08.get());
    trans_field->addChild(trans_small_09.get());
    trans_field->addChild(trans_small_10.get());
    trans_field->addChild(trans_small_11.get());
    trans_field->addChild(trans_small_12.get());
    
    // flat asteroids
    ref_ptr<ph::Asteroid> asteroid_flat_fine = new ph::Asteroid(5, 20, 20, 2, 3, 1);
    ref_ptr<ph::Asteroid> asteroid_flat_crude = new ph::Asteroid(5, 5, 5, 1, 1, 4);
    ref_ptr<ph::Asteroid> asteroid_flat_small = new ph::Asteroid(2, 5, 5, 4, 1, 1);
    
    // getting the small asteroids to its place
    ref_ptr<MatrixTransform> trans_flat_01 = new MatrixTransform;
    trans_flat_01->setMatrix(Matrix::rotate(PI_4,Vec3(0.0,0.0,1.0))*Matrix::translate(76.0, 3.0, -2.0));
    trans_flat_01->addChild(asteroid_flat_fine.get());
    
    ref_ptr<MatrixTransform> trans_flat_02 = new MatrixTransform;
    trans_flat_02->setMatrix(Matrix::translate(50.0, 7.0, -2.0));
    trans_flat_02->addChild(asteroid_flat_crude.get());
    
    ref_ptr<MatrixTransform> trans_flat_03 = new MatrixTransform;
    trans_flat_03->setMatrix(Matrix::rotate(PI_4,Vec3(1.0,0.0,1.0))*Matrix::translate(-22.0, 7.0, -2.0));
    trans_flat_03->addChild(asteroid_flat_small.get());
    
    // giving the flat asteroids to root
    trans_field->addChild(trans_flat_01.get());
    trans_field->addChild(trans_flat_02.get());
    trans_field->addChild(trans_flat_03.get());
    
    // Creating animation; Rotation of some asteroids
    osg::ref_ptr<osg::AnimationPathCallback> ani_flat_01 = new osg::AnimationPathCallback;
    ani_flat_01->setAnimationPath( ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Y_AXIS,
     NULL, 0, 76, NULL, 0, 3, NULL, 0, -2));
    trans_flat_01->setUpdateCallback( ani_flat_01.get() );
    osg::ref_ptr<osg::AnimationPathCallback> ani_flat_03 = new osg::AnimationPathCallback;
    ani_flat_03->setAnimationPath( ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Y_AXIS,
     NULL, 0, -22, NULL, 0, 7, NULL, 0, -2));
    trans_flat_03->setUpdateCallback( ani_flat_03.get() );
    
    // giving the asteroids a texture
    asteroid_main_fine->setTexture(0, "../Textures/phobos.jpg");
    asteroid_flat_crude->setTexture(0, "../Textures/ceres.jpg");
    asteroid_flat_fine->setTexture(0, "../Textures/ceres.jpg");
    asteroid_flat_small->setTexture(0, "../Textures/phobos.jpg");
    asteroid_small_crude->setTexture(0, "../Textures/ceres.jpg");
    asteroid_small_fine->setTexture(0, "../Textures/phobos.jpg");
    
    return trans_field.release();
} 

// Extends the created asteroid field by creating copies of one existing field
// and moving them to different directions based on pos(x,y,z)
MatrixTransform* ph::extendAsteroidField(double x, double y, double z) {
    ref_ptr<Group> asteroid_field = ph::createAsteroidField();
    ref_ptr<MatrixTransform> asteroid_copy_01 = new MatrixTransform;
    asteroid_copy_01->setMatrix(Matrix::translate(0.0,0.0,30));
    asteroid_copy_01->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_02 = new MatrixTransform;
    asteroid_copy_02->setMatrix(Matrix::translate(120.0,0.0,0.0));
    asteroid_copy_02->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_03 = new MatrixTransform;
    asteroid_copy_03->setMatrix(Matrix::rotate(PI,Vec3(0.0,1.0,0.0)));
    asteroid_copy_03->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_04 = new MatrixTransform;
    asteroid_copy_04->setMatrix(Matrix::rotate(PI,Vec3(1.0,0.0,0.0))*Matrix::translate(-120.0,0.0,0.0));
    asteroid_copy_04->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_05 = new MatrixTransform;
    asteroid_copy_05->setMatrix(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(120.0,0.0,30));
    asteroid_copy_05->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_06 = new MatrixTransform;
    asteroid_copy_06->setMatrix(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(-120.0,0.0,30));
    asteroid_copy_06->addChild(asteroid_field.get());
    
    ref_ptr<MatrixTransform> root = new MatrixTransform;
    root->setMatrix(Matrix::translate(x,y,z));
    root->addChild(asteroid_copy_06.get());
    root->addChild(asteroid_copy_05.get());
    root->addChild(asteroid_copy_04.get());
    root->addChild(asteroid_copy_03.get());
    root->addChild(asteroid_copy_02.get());
    root->addChild(asteroid_copy_01.get());
    return root.release();
}       

// Creates the flight path of our turian spacecraft
AnimationPath* ph::createTurianFlightPath(double x0, double y0, double z0) {
    
    ref_ptr<AnimationPath> path = new AnimationPath;
    path->setLoopMode( osg::AnimationPath::NO_LOOPING );
    
    double start_time = 60.0;
    double rotation_time = 30.0;
    double return_time = 60.0;
    double start_distance = 800.0;
    double return_distance = 800.0;
    double new_x0 = x0, new_y0 = y0;
    
    unsigned int numSamples = (int)start_time;
    
    // Iterationsschritte bestimmen
    float delta_rot = (3*PI)/(4*rotation_time); // Rotation um func in time
    float delta_pos = 1 / start_time; // Bewegung um factor* func in time
 
    // Pfad für ersten Teilweg zusammensetzen   
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float d_pos = delta_pos * (float)i;
        new_x0 = (float)lin_f(start_distance,d_pos,x0);
        Vec3 pos( new_x0, y0, z0 );
        path->insert( (float)i, AnimationPath::ControlPoint(pos) );
    }
    
    numSamples = (int) rotation_time;
    
    // Pfad für die Rotation zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( new_x0, y0, z0 );
        Quat rot(yaw, Vec3(0.0, 0.0, -1.0));
        path->insert( (float)(start_time+i), AnimationPath::ControlPoint(pos,rot) );
    }
    
    delta_pos = 1 / return_time;
    numSamples = (int) return_time;
    x0= new_x0; y0= new_y0;
    
    // Pfad für den Rückweg zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float d_pos = delta_pos * (float)i;
        new_x0 = (float)lin_f(-return_distance,d_pos,x0);
        new_y0 = (float)lin_f(-return_distance/2,d_pos,y0);
        Vec3 pos( new_x0, new_y0, z0 );
        Quat rot(3*PI/4, Vec3(0.0, 0.0, -1.0));
        path->insert( (float)(start_time+rotation_time+i), AnimationPath::ControlPoint(pos,rot) );
    }
    
    return path.release();
 }
 
 // Creates a comet with a particle tail
Group* ph::createComet(double x, double y, double z) { 
    ref_ptr<ph::Asteroid> asteroid = new ph::Asteroid(12, 20, 20, 1, 1, 1);
    asteroid->setTexture(0, "../Textures/phobos.jpg");
    double delta_x = 800.0, delta_y = 2000.0;
    
    // getting the big asteroids to its place
    ref_ptr<MatrixTransform> trans_asteroid = new MatrixTransform;
    trans_asteroid->setMatrix(Matrix::translate(x, y, z));
    trans_asteroid->addChild(asteroid.get());
    
    // creating animation path for comet
    osg::ref_ptr<osg::AnimationPathCallback> animation_asteroid = new osg::AnimationPathCallback;
    animation_asteroid->setAnimationPath( ph::createAnimationPath(600.0f, 20*PI, ph::LOOP, ph::NEG_X_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y, NULL, 0, z));
    trans_asteroid->setUpdateCallback( animation_asteroid.get() );
    
    //Moving the origin of particles
    ref_ptr<MatrixTransform> mt = new MatrixTransform();
    mt->setMatrix( Matrix::translate(x, y-5, z) );

    //Creating the particlesystem at the point defined above
    ref_ptr<ParticleSystem> ps = createParticleSystem(mt.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);
    
    // Creating Animation; Movement of the particles
    osg::ref_ptr<osg::AnimationPathCallback> animation_particle = new osg::AnimationPathCallback;
    animation_particle->setAnimationPath( ph::createAnimationPath(600.0f, 0, ph::LOOP, ph::NO_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y, NULL, 0, z));
    mt->setUpdateCallback( animation_particle.get() );
    
    // Parent node to separate asteroid and his animation from the particle animation
    ref_ptr<Group> node = new Group();
    
    node->addChild(trans_asteroid.get());
    node->addChild(updater.get());
    node->addChild(mt.get());
    
    return node.release();
}

// Creating particle system for Comet
ParticleSystem* ph::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    ps->getDefaultParticleTemplate().setShape(Particle::POINT);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Texture erzeugen
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
    rrc->setRateRange( 100, 1000 );
    
    //makeshooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-2.5,-0.5); // Streuung z-x-ebene gegen UZS
    myshooter->setPhiRange(0.5,2.5); //Streuung x-y-ebene gegen UZS
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

//creates 1d texture based on osgtexture1d code example
StateSet* ph::createTorusTexture(Geode* model) {
    Image* image = new Image;
    int pixels = 1000;
    
    // image anlegen mit pixels x 1 x 1 und RGBA dargestellt durch Vec4
    image->allocateImage(pixels,1,1,GL_RGBA,GL_FLOAT);
    image->setInternalTextureFormat(GL_RGBA);
    
    // creating colors
    vector<Vec4> colorBands;
    colorBands.push_back(Vec4(0.0,0.0,0.0,1.0));
    colorBands.push_back(Vec4(0.1,0.1,0.1,1.0));
    colorBands.push_back(Vec4(0.2,0.2,0.2,1.0));
    colorBands.push_back(Vec4(0.3,0.3,0.3,1.0));
    colorBands.push_back(Vec4(1.0,1.0,1.0,1.0));
    
    float band_size = colorBands.size();
    float delta = band_size / (float) pixels;
    int pos = 0, count = 0;
    
    /* creating image data (% Pixel; symmetrical)
       10 % dark grey; 3% black; 5% light grey;
       2% black; 10% light grey; 2% black;
       5% light grey; 3% black; 5% light grey
       5% dark grey*/
    Vec4* dataPoints = (Vec4*)image->data();
    for (int k=1; k <=2; k++) {
        for(int i=0; i<pixels/10; i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/10); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[2];
            *dataPoints++ = color;
            count = i;
        }

        pos+= count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }  
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
       pos += count;
       for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
            count = i;
        }
        pos += count;
    }
    
    Texture1D* texture = new Texture1D;
    texture->setWrap(Texture1D::WRAP_T, Texture::MIRROR);
    texture->setFilter(Texture1D::MIN_FILTER, Texture::NEAREST);
    texture->setImage(image);
    
    Material* material = new Material;
    StateSet* stateSet = new StateSet;
    
    stateSet->setTextureAttribute(0,texture, StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_1D, StateAttribute::ON| StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_2D, StateAttribute::OFF| StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_3D, StateAttribute::OFF| StateAttribute::OVERRIDE);
    
    stateSet->setAttribute(material, StateAttribute::OVERRIDE);
    
    return stateSet;
}
