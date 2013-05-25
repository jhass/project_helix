#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include "objects/Ship.h"
#include "objects/Nebula.h"
#include "objects/Asteroid.h"
#include "objects/Sphere.h"
#include "objects/Torus.h"

#include "MainScene.h"

using namespace osg;

ph::MainScene::MainScene() {
    ref_ptr<Node> ship = new ph::Ship();
    
    //Parameterliste: Verschiebungsvektor-Pointer
    ref_ptr<Node> nebula = new ph::Nebula(new Vec3d(-100,-30,40)); //hinter, rechts, drüber
    
    //Parameterliste: ?,?,?,?,?
    ref_ptr<ph::Asteroid> asteroid = new ph::Asteroid(2, 20, 20, 2, 1, 3);
    asteroid->setTexture(0, "../Textures/EarthMap.jpg"); //Wird beim Zoomen Blau? WTF?
    ref_ptr<MatrixTransform> asttrans = new MatrixTransform();
    asttrans->setMatrix(Matrix::translate(Vec3d(200,0,50))); //vor, -, drüber
    asttrans->addChild(asteroid.get());

    //Parameterliste: Radius, Auflösung, Auflösung
    ref_ptr<ph::Sphere> planet = new ph::Sphere(1000, 200, 200);
    planet->setTexture(0, "../Textures/EarthMap.jpg"); //Auch Blau?
    ref_ptr<MatrixTransform> plantrans = new MatrixTransform();
    plantrans->setMatrix(Matrix::translate(Vec3d(0,1200,-100)));
    plantrans->addChild(planet.get());

    //Parameterliste: Radius zur mitte, Breite(wtf?), Auflösung?, Auflösung?
    ref_ptr<ph::Torus> torus = new ph::Torus(1600, 300, 100, 100);
    ref_ptr<Group> torusroot = new Group();
    torusroot->addChild(torus.get());
    torus->setStyle(ph::Torus::FLAT);
    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile("../Textures/EarthMap.jpg"); //Hat trotzdem keine Textur
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP);
    texture->setImage(image.get());
    torusroot->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    ref_ptr<MatrixTransform> torustrans = new MatrixTransform();
    torustrans->setMatrix(Matrix::translate(Vec3d(0,1200,-100)));
    torustrans->addChild(torus.get());    

    this->addChild(torustrans.get());
    this->addChild(plantrans.get());
    this->addChild(asttrans.get());
    this->addChild(ship.get());
    this->addChild(nebula.get());
    // this->addChild(ph::getDebugAxes(10, 0, 0, 0));
}
