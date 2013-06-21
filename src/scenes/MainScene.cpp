#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgParticle/ParticleSystemUpdater>
#include <osg/ShapeDrawable>

#include "objects/Skybox.h"
#include "objects/Sun.h"
#include "objects/Nebula.h"
#include "objects/Asteroid.h"
#include "objects/Sphere.h"
#include "objects/Torus.h"
#include "objects/Chronos.h"
#include "objects/Reaper.h"

#include "util.h"
#include "scene_utils.h"

#include "MainScene.h"

using namespace osg;

ph::MainScene::MainScene() {   
    createSkyboxAndSuns();
    createPlanet();
    createStation();
    createShip();
    createAsteroidField();
    createComet();
    createCuboid();
    createReaper();   
    createNebula();

    this->addChild(ph::getDebugAxes(20, 0, 0, 0));
}

void ph::MainScene::createSkyboxAndSuns() {
    int height = 4000;
    int width = 4000;

    // ref-Pointer anlegen
    ref_ptr<ph::Skybox> skybox = new ph::Skybox(height, width);

    // Texturen für die Rechtecke festlegen
    for (ph::Skybox::Position s = ph::Skybox::FRONT; s <= ph::Skybox::BOTTOM; s++) {
        skybox->setTexture(s,  0, "../resources/skybox.jpg");
    }
    
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun_orange = new ph::Sun(100, 200, 0, 0.9, 0.6, 0);
    
    // translating sun and adding it so skybox
    ref_ptr<MatrixTransform> suntrans_or = new MatrixTransform;
    suntrans_or->setMatrix(Matrix::translate(Vec3(800, width, 0)));
    skybox->clampObjectToSkybox(suntrans_or);
    suntrans_or->addChild(sun_orange.get());
    
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun_violet = new ph::Sun(50, 200, 1, 0.9, 0.0, 0.6);
    
    // translating sun and adding it so skybox
    ref_ptr<MatrixTransform> suntrans_vl = new MatrixTransform();
    suntrans_vl->setMatrix(Matrix::translate(Vec3(height, 800, 0)));
    skybox->clampObjectToSkybox(suntrans_vl);
    suntrans_vl->addChild(sun_violet.get());

    // Activate light of the suns
    this->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    this->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    
    this->addChild(skybox.get());
}

void ph::MainScene::createPlanet() {
    double x =   0;
    double y = 800;
    double z =   0;

    ref_ptr<MatrixTransform> planet = new MatrixTransform;

    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(500, 200);
    
    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/mars_map.jpg");
    
    // Torus(innerRadius, torusRadius, lengthSteps, widthSteps)
    ref_ptr<ph::Torus> torus = new ph::Torus(650, 75, 200);

    // NORMAL is Default
    torus->setStyle(ph::Torus::FLAT);
    torus->setStateSet(ph::createTorusTexture(torus));
       
    planet->setMatrix(Matrix::translate(x, y, z));
    planet->addChild(sphere.get());
    planet->addChild(torus.get());
    
    // Creating Animation; Rotation of the planet
    osg::ref_ptr<osg::AnimationPathCallback> animation_planet = new osg::AnimationPathCallback;
    animation_planet->setAnimationPath(
        ph::createAnimationPath(600.0f, 2*PI, ph::LOOP, ph::POS_Z_AXIS,
                                NULL, 0, x, NULL, 0, y, NULL, 0, z)
    );
    planet->setUpdateCallback(animation_planet.get() );
    
    this->addChild(planet.get());
}

void ph::MainScene::createStation() {
    ref_ptr<MatrixTransform> station = new MatrixTransform;
    station->addChild(new ph::Chronos);
    station->setMatrix(
        Matrix::rotate(-PI_2, Vec3(0, 0, 1)) *
        Matrix::translate(Vec3(-20, 80, 100))
    );
    this->addChild(station.get());
}

void ph::MainScene::createShip() {
    ship = new ph::Ship;
    ref_ptr<MatrixTransform> trans_ship = new MatrixTransform;
    trans_ship->setMatrix(Matrix::translate(-850, 80, 100));
    this->addChild(ship.get());
}


void ph::MainScene::createAsteroidField() {
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
    
    // return trans_field.release();

// Extends the created asteroid field by creating copies of one existing field
// and moving them to different directions based on pos(x,y,z)

    ref_ptr<MatrixTransform> root = new MatrixTransform;
    root->setMatrix(Matrix::translate(20, -600, 0));

    ref_ptr<Group> asteroid_field = trans_field;
    ref_ptr<MatrixTransform> asteroid_copy_01 = new MatrixTransform;
    asteroid_copy_01->setMatrix(Matrix::translate(0.0,0.0,30));
    asteroid_copy_01->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_02 = new MatrixTransform;
    asteroid_copy_02->setMatrix(Matrix::translate(200.0,0.0,0.0));
    asteroid_copy_02->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_03 = new MatrixTransform;
    asteroid_copy_03->setMatrix(Matrix::rotate(PI,Vec3(0.0,1.0,0.0)));
    asteroid_copy_03->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_04 = new MatrixTransform;
    asteroid_copy_04->setMatrix(Matrix::rotate(PI,Vec3(1.0,0.0,0.0))*Matrix::translate(-200.0,0.0,0.0));
    asteroid_copy_04->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_05 = new MatrixTransform;
    asteroid_copy_05->setMatrix(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(200.0,0.0,30));
    asteroid_copy_05->addChild(asteroid_field.get());
    ref_ptr<MatrixTransform> asteroid_copy_06 = new MatrixTransform;
    asteroid_copy_06->setMatrix(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(-200.0,0.0,30));
    asteroid_copy_06->addChild(asteroid_field.get());
    
    root->addChild(asteroid_copy_06.get());
    root->addChild(asteroid_copy_05.get());
    root->addChild(asteroid_copy_04.get());
    root->addChild(asteroid_copy_03.get());
    root->addChild(asteroid_copy_02.get());
    root->addChild(asteroid_copy_01.get());

    this->addChild(root.get());
}   

void ph::MainScene::createComet() { 
    double x = 200;
    double y = -1000;
    double z = 200;

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
    mt->setMatrix( Matrix::translate(x, y+5, z) );

    //Creating the particlesystem at the point defined above
    ref_ptr<ParticleSystem> ps = createParticleSystem(mt.get());
    ref_ptr<ParticleSystemUpdater> updater = new ParticleSystemUpdater();
    updater->addParticleSystem(ps);
    
    // Creating Animation; Movement of the particles
    osg::ref_ptr<osg::AnimationPathCallback> animation_particle = new osg::AnimationPathCallback;
    animation_particle->setAnimationPath( ph::createAnimationPath(600.0f, 0, ph::LOOP, ph::NO_AXIS,
     lin_f, delta_x, x, lin_f, delta_y, y+5, NULL, 0, z));
    mt->setUpdateCallback( animation_particle.get() );
    
    // Parent node to separate asteroid and his animation from the particle animation
    ref_ptr<Group> node = new Group();
    
    node->addChild(trans_asteroid.get());
    node->addChild(updater.get());
    node->addChild(mt.get());
    
    this->addChild(node.get());
}

void ph::MainScene::createCuboid() {
    double x = 0;
    double y = -200;
    double z = 15;

    ref_ptr<MatrixTransform> root = new MatrixTransform;

    ref_ptr<Geode> cuboid = new Geode;
    cuboid->addDrawable(new ShapeDrawable(new Box(Vec3(0, 0, 0), 1, 3, 0.25)));
    
    // Creating Material for the Cuboid
    ref_ptr<Material> material = new Material;
    // material emits giving light (R,G,B,x)
    material->setEmission(Material::FRONT_AND_BACK, Vec4(0,0,0,1.0));
    
    // material parameters
    material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.1,0.1,0.1,1.0));
    material->setAmbient(Material::FRONT_AND_BACK, Vec4(0,0,0,1.0));
    material->setSpecular(Material::FRONT_AND_BACK, Vec4(1,1,1,1));
    material->setShininess(Material::FRONT_AND_BACK, 30);
    
    // giving the material to the cuboid
    cuboid->getOrCreateStateSet()->setAttributeAndModes(material.get(),StateAttribute::ON);
    
    // translating cuboid to startposition
    root->setMatrix(Matrix::translate(x,y,z));
    
    // animating cuboid flight path
    osg::ref_ptr<osg::AnimationPathCallback> ani_cuboid = new osg::AnimationPathCallback;
    ani_cuboid->setAnimationPath( ph::createAnimationPath(1800, 0, ph::LOOP, ph::NO_AXIS,
     NULL, 0, x, lin_f, 400-y, y, NULL, 0, z));
    root->setUpdateCallback( ani_cuboid.get() );
    
    root->addChild(cuboid.get());
    this->addChild(root.get());
}

void ph::MainScene::createReaper() {
    // Create Reaper Spaceship
    ref_ptr<MatrixTransform> reaper = new MatrixTransform;
    reaper->setMatrix(Matrix::rotate(PI_2+PI/10,Vec3(0,0,1)));
    ref_ptr<MatrixTransform> reaper_node = new MatrixTransform;
    reaper_node->addChild(reaper.get());
    ref_ptr<osg::AnimationPathCallback> ani_reaper = new osg::AnimationPathCallback;
    ani_reaper->setAnimationPath(ph::createReaperFlightPath(2000,40,500,80,-300,90));
    reaper_node->setUpdateCallback(ani_reaper.get());
    this->addChild(reaper_node.get());
    reaper->addChild(new ph::Reaper);
    this->addChild(reaper.get());
}

void ph::MainScene::createNebula() {
    this->addChild(new ph::Nebula(Vec3d(1800, 500, -300), "../resources/nebulainner.png", 50, 75));
}
