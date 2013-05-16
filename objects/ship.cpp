#include <osgDB/ReadFile>

#include "ship.h"

string ph::Ship::fileLocation = "../resources/cruiser.obj";
 
ph::Ship::Ship() {
    this->addChild(osgDB::readNodeFile(fileLocation));
}
