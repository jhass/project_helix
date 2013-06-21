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
#include "objects/PlanetRing.h"
#include "objects/Comet.h"
#include "objects/AsteroidField.h"

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

Node* ph::MainScene::addTransformedNode(Node* node, const Matrix& matrix) {
    ref_ptr<MatrixTransform> transform = new MatrixTransform;
    transform->setMatrix(matrix);
    transform->addChild(node);
    this->addChild(transform.get());
    return transform.release();
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
    ref_ptr<ph::PlanetRing> ring = new ph::PlanetRing(650, 75, 200);

       
    planet->setMatrix(Matrix::translate(x, y, z));
    planet->addChild(sphere.get());
    planet->addChild(ring.get());
    
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
    addTransformedNode(new ph::Chronos,
        Matrix::rotate(-PI_2, Vec3(0, 0, 1)) *
        Matrix::translate(Vec3(-20, 80, 100))
    );
}

void ph::MainScene::createShip() {
    ship = new ph::Ship;
    this->addChild(ship.get());
}


void ph::MainScene::createAsteroidField() {
    addTransformedNode(new ph::AsteroidField, Matrix::translate(20, -600, 0));
}   

void ph::MainScene::createComet() { 
    ref_ptr<ph::Comet> comet = new ph::Comet(12, 20, 20, 1, 1, 1);
    comet->translateAndAnimate(200, -1000, 200);
    this->addChild(comet.get());
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
    
    // animating cuboid flight path
    osg::ref_ptr<osg::AnimationPathCallback> ani_cuboid = new osg::AnimationPathCallback;
    ani_cuboid->setAnimationPath( ph::createAnimationPath(1800, 0, ph::LOOP, ph::NO_AXIS,
     NULL, 0, x, lin_f, 400-y, y, NULL, 0, z));
    addTransformedNode(cuboid.get(), Matrix::translate(x,y,z))->setUpdateCallback(ani_cuboid.get());
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
