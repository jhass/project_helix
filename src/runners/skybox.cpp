#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/Vec3>
#include <osg/MatrixTransform>

#include "3rdparty/osgToy/Normals.h"
#include "objects/Rectangle.h"
#include "objects/Skybox.h"
#include "objects/Sun.h"
#include "objects/Sphere.h"
#include "util.h"

using namespace osgToy;
using namespace osg;

int main(void)
{
    ref_ptr<Group> root = new Group;
    
	// baue Geometry
	ref_ptr<ph::Skybox> skybox = new ph::Skybox(100,100);

	// Lichteffekte für die Skybox ausstellen
	skybox->setTexture(ph::Skybox::FRONT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::BACK,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::LEFT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::RIGHT,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::TOP,0,"../resources/skybox.jpg");
	skybox->setTexture(ph::Skybox::BOTTOM,0,"../resources/skybox.jpg");
    root->addChild(skybox);
    //root->addChild(ph::getDebugAxes(5.0,0.0,10.0,0.0));
    
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200);
    
    // pushing sphere to the right
    ref_ptr<MatrixTransform> spheretrans = new MatrixTransform();
    spheretrans->setMatrix(Matrix::translate(Vec3(-25,50,0)));
    //skybox->clampObjectToSkybox(spheretrans);
    spheretrans->addChild(sphere.get());
    ref_ptr<MatrixTransform> spheretrans2 = new MatrixTransform();
    spheretrans2->setMatrix(Matrix::translate(Vec3(-25,25,0)));
    spheretrans2->addChild(sphere.get());
    root->addChild(spheretrans.get());
    root->addChild(spheretrans2.get());
    
    // giving the sphere a texturefile
    sphere->setTexture(0, "../resources/EarthMap.jpg");
    
    // Sun(radius, Steps, GLLightNumber, red, green, blue)
    ref_ptr<ph::Sun> sun = new ph::Sun(10.0, 200, 0, 0.9, 0.6, 0.0);
    
    // pushing sun to the left
    ref_ptr<MatrixTransform> suntrans = new MatrixTransform();
    suntrans->setMatrix(Matrix::translate(Vec3(100,100,0)));
    skybox->clampObjectToSkybox(suntrans);
    suntrans->addChild(sun.get());
    //root->addChild(suntrans.get());
    root->getOrCreateStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
    
    // enables VertexNormals and FaceNormals
     ref_ptr<VertexNormals> vNormals = new VertexNormals(skybox.get());
     ref_ptr<SurfaceNormals> sNormals = new SurfaceNormals(skybox.get());
    // root->addChild(vNormals.get());
    // root->addChild(sNormals.get());
    
    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //root->getOrCreateStateSet()->setAttribute (pm.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	
	// Hauptkamera manipulieren
	// eye: Kameraposition(x,y,z)
	Vec3 eye(0.0, -40.0, 0.0);
	// center: Punkte, auf den man schaut (x,y,z)
	Vec3 center(0.0, -30.0, 0.0);
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
