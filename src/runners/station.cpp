#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Node>
#include <osg/MatrixTransform>

#include "objects/Chronos.h"
#include "objects/Ship.h"
#include "objects/Reaper.h"
using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group;
    ref_ptr<ph::Chronos> station = new ph::Chronos();
    ref_ptr<ph::Ship> ship = new ph::Ship;
    ref_ptr<ph::Reaper> reaper = new ph::Reaper;
    
    osg::ref_ptr<osg::MatrixTransform> scale_station = new osg::MatrixTransform;
    scale_station->setMatrix( Matrix::scale(4.0, 4.0, 4.0));
    scale_station->addChild(station.get());
    
    osg::ref_ptr<osg::MatrixTransform> trans_ship = new osg::MatrixTransform;
    trans_ship->setMatrix( Matrix::translate(-30.0, 0.0, 0.0));
    trans_ship->addChild(ship.get());
    
    osg::ref_ptr<osg::MatrixTransform> trans_reaper = new osg::MatrixTransform;
    trans_reaper->setMatrix( Matrix::translate(30.0, 0.0, 0.0));
    trans_reaper->addChild(station.get());
    
    root->addChild(reaper.get());
    root->addChild( trans_ship.get() );
    root->addChild( trans_reaper.get() );
 
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
