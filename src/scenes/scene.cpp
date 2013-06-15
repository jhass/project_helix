#include <osgViewer/Viewer>

#include "scene_utils.h"
#include "objects/Skybox.h"

using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group;
    
    // Creating SKYBOX with SUNS
    ref_ptr<ph::Skybox> skybox = ph::createSkybox();
    
    root->addChild(skybox.get());
    // activation light of the suns
    root->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT1, StateAttribute::ON);
    
    //Creating PLANET
    ref_ptr<MatrixTransform> planet = ph::createPlanet();
    root->addChild(planet.get());
    
    //Creating SHIP
    ref_ptr<MatrixTransform> ship = ph::createShip(ph::STATION,-20.0,-500.0,0.0);
    root->addChild(ship.get());
    
    //Creting ASTEROID FIELD
    ref_ptr<MatrixTransform> asteroid = ph::createAsteroidField(20.0,-600.0,0.0);
    root->addChild(asteroid.get());
    
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
