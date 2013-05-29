#include <osgViewer/Viewer>
#include <osg/PolygonMode>

#include "objects/Rectangle.h"

int main(void)
{
	// baue Geometry
	ref_ptr<ph::Rectangle> testrec = new ph::Rectangle(100,50);
	testrec->setTexture(0,"../EarthMap.jpg");

    // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //testrec->getOrCreateStateSet()->setAttribute (pm.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData( testrec.get() );
	return viewer.run();
}
