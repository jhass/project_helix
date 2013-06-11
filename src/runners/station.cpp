#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Node>
#include <osg/MatrixTransform>

#include "objects/Chronos.h"
#include "objects/Ship.h"
using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group;
    ref_ptr<ph::Chronos> station = new ph::Chronos();
    ref_ptr<ph::Ship> ship = new ph::Ship;
    
    osg::ref_ptr<osg::MatrixTransform> scale_station = new osg::MatrixTransform;
    scale_station->setMatrix( Matrix::scale(4.0, 4.0, 4.0));
    scale_station->addChild(station.get());
    
    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->setMatrix( Matrix::translate(-30.0, 0.0, 0.0));
    trans->addChild(ship.get());
    
    root->addChild(station.get());
    //root->addChild( trans.get() );
 
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
