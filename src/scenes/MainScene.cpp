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
    // Creating SKYBOX with SUNS
    ref_ptr<ph::Skybox> skybox = ph::createSkybox(1000,1000);
    
    this->addChild(skybox.get());
    // activation light of the suns
    this->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    this->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    
    // Creating PLANET
    ref_ptr<MatrixTransform> planet = ph::createPlanet(0,800,0);
    this->addChild(planet.get());
    
    // Creating SHIP
    ref_ptr<MatrixTransform> station = ph::createShip(ph::STATION,-20.0, 80.0,100.0);
    station->setMatrix(Matrix::rotate(-PI_2,Vec3(0,0,1))*station->getMatrix());
    this->addChild(station.get());

    ship = new ph::Ship;
    ref_ptr<MatrixTransform> trans_ship = new MatrixTransform;
    trans_ship->setMatrix( Matrix::translate(-850, 80, 100));

    ship_callback = new ShipNodeCallback;
    ship->setUpdateCallback(ship_callback.get());
    this->addChild(ship.get());
    
    // Creating ASTEROID FIELD
    ref_ptr<MatrixTransform> asteroid = ph::extendAsteroidField(20.0,-600.0,0.0);
    this->addChild(asteroid.get());
    
    // Creating COMET
    ref_ptr<Group> comet = ph::createComet(200.0,-1000.0,200.0);
    this->addChild(comet.get());
    // this->addChild(ph::getDebugAxes(1, 3.5, 0, 1.5));
}
