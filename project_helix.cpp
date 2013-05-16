#include <osgViewer/Viewer>

#include "objects/ship.h"
#include "util.h"

using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group();
    ref_ptr<Group> ship = new ph::Ship();
    
    root->addChild(ship);
    root->addChild(ph::getDebugAxes(2, 6.5, 0, 0));
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
