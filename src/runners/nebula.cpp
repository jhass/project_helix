#include <osgViewer/Viewer>

#include "objects/Nebula.h"

using namespace osgViewer;

int main(void) {
    ref_ptr<ph::Nebula> nebula = new ph::Nebula(Vec3d(-100, -30, 40));

    Viewer viewer;
    viewer.setSceneData(nebula.get());
    return viewer.run();
}
