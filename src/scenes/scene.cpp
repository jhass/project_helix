#include <osgViewer/Viewer>

#include "scene_utils.h"
#include "objects/Skybox.h"

using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group;
    
    // Creating SKYBOX with SUNS
    ref_ptr<ph::Skybox> skybox = ph::createSkybox(1000,1000);
    
    root->addChild(skybox.get());
    // activation light of the suns
    root->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    
    // Creating PLANET
    ref_ptr<MatrixTransform> planet = ph::createPlanet(0,800,0);
    root->addChild(planet.get());
    
    // Creating SHIP
    ref_ptr<MatrixTransform> ship = ph::createShip(ph::STATION,-20.0, 80.0,100.0);
    ship->setMatrix(Matrix::rotate(-PI_2,Vec3(0,0,1))*ship->getMatrix());
    root->addChild(ship.get());
    ref_ptr<MatrixTransform> turian_ship = ph::createShip(ph::TURIAN,-850.0,80.0,100.0);
    osg::ref_ptr<osg::AnimationPathCallback> turian_path = new osg::AnimationPathCallback;
    turian_path->setAnimationPath( ph::createTurianFlightPath(-850.0,80.0,100.0));
    turian_ship->setUpdateCallback( turian_path.get() );
    root->addChild(turian_ship.get());
    
    // Creating ASTEROID FIELD
    ref_ptr<MatrixTransform> asteroid = ph::extendAsteroidField(20.0,-600.0,0.0);
    root->addChild(asteroid.get());
    
    // Creating COMET
    ref_ptr<Group> comet = ph::createComet(200.0,-1000.0,200.0);
    root->addChild(comet.get());
    
    
    osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	
	// Hauptkamera manipulieren
	// eye: Kameraposition(x,y,z)
	Vec3 eye(0.0, -700.0, 0.0);
	// center: Punkte, auf den man schaut (x,y,z)
	Vec3 center(0.0, 10.0, 0.0);
	// up: natürliche Aufwärtsrichtung (x,y,z)
	Vec3 up(0.0, 0.0, 1.0);
	
	// Projektion als Zentralprojektion festlegen (left, right, bottom, top, near, far)
	viewer.getCamera()->setProjectionMatrixAsFrustum(-0.35, 0.35, -0.26, 0.26, 1.0, 10000);
	// Übergeben der neuen Kameraeinstellungen
	viewer.getCamera()->setViewMatrixAsLookAt(eye, center, up);
	// Kamera Manipulator ausstellen, sonst werden Einstellungen nicht übernommen
	//viewer.getCamera()->setAllowEventFocus(false);
		
	return viewer.run();
}
