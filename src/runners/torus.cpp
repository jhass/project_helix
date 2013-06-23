#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>

#include "3rdparty/osgToy/Normals.h"

#include "objects/Torus.h"

using namespace osgToy;

int main(void) {
    // Torus(innerRadius, torusRadius, lengthSteps, widthSteps)
    ref_ptr<ph::Torus> torus = new ph::Torus(6, 1.5, 100);
    ref_ptr<Group> root = new Group();
    root->addChild(torus.get());

    // Default ist NORMAL
    torus->setStyle(ph::Torus::FLAT);
    
    // Textur setzen
    torus->setTexture(0,"../resources/EarthMap.jpg");
    
    // Alternativ: normal Torus
    //ref_ptr<ph::Torus> torus = new ph::FlatTorus(6, 1.5, 75);

    // enables VertexNormals and FaceNormals
    // ref_ptr<VertexNormals> vNormals = new VertexNormals(torus.get());
    // ref_ptr<SurfaceNormals> sNormals = new SurfaceNormals(torus.get());
    // root->addChild(vNormals.get());
    // root->addChild(sNormals.get());

    // enables PolygonMode
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
