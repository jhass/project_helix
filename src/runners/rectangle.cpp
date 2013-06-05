#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "3rdparty/osgToy/Normals.h"
#include "objects/Rectangle.h"

using namespace osgToy;

int main(void)
{
    ref_ptr<Group> root = new Group;
	// baue Geometry
	ref_ptr<ph::Rectangle> testrec = new ph::Rectangle(100,50);
	testrec->setTexture(0,"../Textures/EarthMap.jpg");
	testrec->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);
	root->addChild(testrec.get());
	
	// enables VertexNormals and FaceNormals
     ref_ptr<VertexNormals> vNormals = new VertexNormals(testrec.get());
     ref_ptr<SurfaceNormals> sNormals = new SurfaceNormals(testrec.get());
     root->addChild(vNormals.get());
     root->addChild(sNormals.get());

    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //testrec->getOrCreateStateSet()->setAttribute (pm.get());
    

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	return viewer.run();
}
