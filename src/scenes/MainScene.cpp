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

ph::MainScene::MainScene() {
    ship = new ph::Ship();
    ship_callback = new ph::ShipNodeCallback;
    ship->setUpdateCallback(ship_callback.get());
    
    //Parameterliste: Verschiebungsvektor-Pointer
    ref_ptr<Node> nebula = new ph::Nebula(Vec3d(-100,-30,40), "../resources/nebulainner.png", 10, 50); //hinter, rechts, drüber
    
    //Parameterliste: radius,length,height,deformation x,y,z
    ref_ptr<ph::Asteroid> asteroid = new ph::Asteroid(2, 20, 20, 2, 1, 1);
    asteroid->setTexture(0, "../Textures/EarthMap.jpg"); //Wird beim Zoomen Blau? WTF?
    ref_ptr<MatrixTransform> asttrans = new MatrixTransform();
    asttrans->setMatrix(Matrix::translate(Vec3d(200,0,50))); //vor, -, drüber
    asttrans->addChild(asteroid.get());

    //Parameterliste: Radius, Auflösung, Auflösung
    ref_ptr<ph::Sphere> planet = new ph::Sphere(1000, 200);
    planet->setTexture(0, "../Textures/EarthMap.jpg"); //Auch Blau?
    ref_ptr<MatrixTransform> plantrans = new MatrixTransform();
    plantrans->setMatrix(Matrix::translate(Vec3d(0,1200,-100)));
    plantrans->addChild(planet.get());

    //Parameterliste: Radius zur mitte, Breite(wtf?), Auflösung?, Auflösung?
    ref_ptr<ph::Torus> torus = new ph::Torus(1600, 300, 100);
    torus->setTexture(0, "../Textures/EarthMap.jpg");
    ref_ptr<MatrixTransform> torustrans = new MatrixTransform();
    torustrans->setMatrix(Matrix::translate(Vec3d(0,1200,-100)));
    torustrans->addChild(torus.get());

    this->addChild(torustrans.get());
    this->addChild(plantrans.get());
    this->addChild(asttrans.get());
    this->addChild(ship.get());
    this->addChild(nebula.get());
    // this->addChild(ph::getDebugAxes(1, 3.5, 0, 1.5));
}
