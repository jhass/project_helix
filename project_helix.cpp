#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include "objects/ship.h"

using namespace osg;
int main(void) {
    ref_ptr<Group> root = new Group();
    ref_ptr<Node> ship = new Ship();
    
    root->addChild(ship);
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}
