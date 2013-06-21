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
    ref_ptr<ph::Skybox> skybox = ph::createSkybox(4000, 4000);
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
    
    // Create asteroid field 
    ref_ptr<MatrixTransform> asteroid = ph::extendAsteroidField(20, -600, 0);
    this->addChild(asteroid.get());

    // Create nebula
    this->addChild(new ph::Nebula(Vec3d(1800, 500, -300), "../resources/nebulainner.png", 50, 75));
    
    // Create comet
    ref_ptr<Group> comet = ph::createComet(200, -1000, 200);
    this->addChild(comet.get());
    
    // Create Cuboid
    ref_ptr<MatrixTransform> cuboid = ph::createCuboid(0,-200,15);
    this->addChild(cuboid.get());
    
    // Create Reaper Spaceship
    ref_ptr<MatrixTransform> reaper = ph::createShip(ph::REAPER, 0, 0, 0);
    reaper->setMatrix(Matrix::rotate(PI_2+PI/10,Vec3(0,0,1)));
    ref_ptr<MatrixTransform> reaper_node = new MatrixTransform;
    reaper_node->addChild(reaper.get());
    ref_ptr<osg::AnimationPathCallback> ani_reaper = new osg::AnimationPathCallback;
    ani_reaper->setAnimationPath(ph::createReaperFlightPath(2000,40,500,80,-300,90));
    reaper_node->setUpdateCallback(ani_reaper.get());
    this->addChild(reaper_node.get());
    
    
    this->addChild(ph::getDebugAxes(20, 0, 0, 0));
}
