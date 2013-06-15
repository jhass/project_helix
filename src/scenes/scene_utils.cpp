#include <osg/MatrixTransform>

#include "util.h"
#include "scene_utils.h"
#include "objects/Skybox.h"
#include "objects/Sun.h"
#include "objects/Ship.h"
#include "objects/Chronos.h"
#include "objects/Reaper.h"
#include "objects/Asteroid.h"

// Creating Skybox with Texture and two suns clamped to the skybox
ph::Skybox* ph::createSkybox() {
    int skybox_height = 1000, skybox_width = 1000;
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
MatrixTransform* ph::createPlanet() {
    ref_ptr<MatrixTransform> planet = new MatrixTransform;
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(500, 200);
    
    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    planet->setMatrix( Matrix::translate(0.0, 800.0, 0.0));
    planet->addChild( sphere.get());
    
    // Creating Animation; Rotation of the planet
    osg::ref_ptr<osg::AnimationPathCallback> animation_planet = new osg::AnimationPathCallback;
    animation_planet->setAnimationPath( ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Z_AXIS,
     NULL, 0, 0, NULL, 0, 800, NULL, 0, 0));
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

// Creating an asteroid field and position(x,y,z)
MatrixTransform* ph::createAsteroidField(double x, double y, double z) {
    ref_ptr<MatrixTransform> trans_field = new MatrixTransform;
    trans_field->setMatrix(Matrix::translate(x,y,z));
    
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
