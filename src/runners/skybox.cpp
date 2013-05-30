#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "3rdparty/osgToy/Normals.h"
#include "objects/Rectangle.h"
#include "objects/Skybox.h"
#include "util.h"

using namespace osgToy;
using namespace osg;

int main(void)
{
    ref_ptr<Group> root = new Group;
	// baue Geometry
	ref_ptr<ph::Skybox> skybox = new ph::Skybox(33,97);
	skybox->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);
    root->addChild(skybox);
    //root->addChild(ph::getDebugAxes(42.0,0.0,0.0,0.0));
    
    // enables VertexNormals and FaceNormals
     ref_ptr<VertexNormals> vNormals = new VertexNormals(skybox.get());
     ref_ptr<SurfaceNormals> sNormals = new SurfaceNormals(skybox.get());
     root->addChild(vNormals.get());
     root->addChild(sNormals.get());
    
    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //root->getOrCreateStateSet()->setAttribute (pm.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	return viewer.run();
}
