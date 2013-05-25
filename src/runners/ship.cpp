#include <osgViewer/Viewer>

#include <objects/Ship.h>

using namespace osgViewer;

int main(void) {
    ref_ptr<ph::Ship> ship = new ph::Ship;
    Viewer viewer;
    viewer.setSceneData(ship.get());
    return viewer.run();
}
