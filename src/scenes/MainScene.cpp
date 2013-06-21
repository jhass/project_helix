#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include "objects/Nebula.h"
#include "objects/Asteroid.h"
#include "objects/Sphere.h"
#include "objects/Torus.h"

#include "util.h"

#include "MainScene.h"

using namespace osg;

#include "scene_utils.h"
#include "util.h"

ph::MainScene::MainScene() {   
    // Create SKYBOX with SUNS
    ref_ptr<ph::Skybox> skybox = ph::createSkybox(1000, 1000);
    this->addChild(skybox.get());

    // Activate light of the suns
    this->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    this->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    
    // Create Planet
    ref_ptr<MatrixTransform> planet = ph::createPlanet(0, 800, 0);
    this->addChild(planet.get());
    
    // Create Station
    ref_ptr<MatrixTransform> station = ph::createShip(ph::STATION, -20, 80, 100);
    station->setMatrix(Matrix::rotate(-PI_2, Vec3(0, 0, 1)) * station->getMatrix());
    this->addChild(station.get());

    // Create ship
    ship = new ph::Ship;
    ref_ptr<MatrixTransform> trans_ship = new MatrixTransform;
    trans_ship->setMatrix(Matrix::translate(-850, 80, 100));
    this->addChild(ship.get());

    ship_callback = new ShipNodeCallback;
    ship->setUpdateCallback(ship_callback.get());
    
    // Create asteroid field 
    ref_ptr<MatrixTransform> asteroid = ph::extendAsteroidField(20, -600, 0);
    this->addChild(asteroid.get());
    
    // Create comet
    ref_ptr<Group> comet = ph::createComet(200, -1000, 200);
    this->addChild(comet.get());
    
    // Create Cuboid
    ref_ptr<MatrixTransform> cuboid = ph::createCuboid(0,-200,15);
    this->addChild(cuboid.get());
    
    // Create Reaper Spaceship
    ref_ptr<MatrixTransform> reaper = ph::createShip(ph::REAPER, 750, 0, 150);
    reaper->setMatrix(Matrix::rotate(PI_2, Vec3(0, 0, 1)) * reaper->getMatrix());
    this->addChild(reaper.get());
    
    
    this->addChild(ph::getDebugAxes(20, 0, 0, 0));
}
