#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Fog>

using namespace osg;
int main(void) {
    ref_ptr<Group> root = new Group();
    ref_ptr<Node> ship = osgDB::readNodeFile( "../resources/cruiser.obj" );
    
    root->addChild(ship);
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
