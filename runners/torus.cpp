#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>

#include "../3rdparty/osgToy/Normals.h"
using namespace osgToy;

#include "../objects/torus.h"


int main(void) {
    ref_ptr<ph::Torus> torus = new ph::Torus(8, 1.5, 75, 75);
    ref_ptr<Group> root = new Group();
    root->addChild(torus.get());

    // Zum Normalen anschauen
    ref_ptr<VertexNormals> vNormals = new VertexNormals(torus.get());
    ref_ptr<SurfaceNormals> sNormals = new SurfaceNormals(torus.get());
    root->addChild(vNormals.get());
    root->addChild(sNormals.get());

    // Wenn man die Dreiecke mal sehen will:
    // ref_ptr<PolygonMode> pm = new PolygonMode;
    // pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
