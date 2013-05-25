#include <osgViewer/Viewer>

#include "objects/ship.h"
#include "objects/nebula.h"
#include "util.h"

using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group();
    ref_ptr<Group> ship = new ph::Ship();
    ref_ptr<Group> nebula = new ph::Nebula(new Vec3d(10,10,0));
    
    root->addChild(ship);
    root->addChild(nebula);
    root->addChild(ph::getDebugAxes(2, 6.5, 0, 0));
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
