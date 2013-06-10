#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osg/Node>
#include <osg/StateSet>
#include <osg/ShadeModel>

#include "objects/Chronos.h"
using namespace osg;

int main(void) {
    ref_ptr<Group> root = new Group;
    ref_ptr<ph::Chronos> station = new ph::Chronos();
    
    root->addChild(station.get());
    
 
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
