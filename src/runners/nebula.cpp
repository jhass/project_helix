#include <osgViewer/Viewer>

#include "objects/Nebula.h"

using namespace osgViewer;

int main(void) {
	Vec3d location =Vec3d(-100, -30, 40);
    ref_ptr<ph::Nebula> nebula = new ph::Nebula(location, "../resources/nebulainner.png",
    											 10, 50);

    Vec3d locationtwo =Vec3d(-100, -30, 40);
    ref_ptr<ph::Nebula> nebulatwo = new ph::Nebula(locationtwo, "../resources/nebulaouter.png",
    											 25, 75);

    ref_ptr<Group> root = new Group();

    root->addChild(nebula.get());
    root->addChild(nebulatwo.get());
    Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
