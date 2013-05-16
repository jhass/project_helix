#include "ship.h"

std::string Ship::fileLocation = "../resources/cruiser.obj";
 
Ship::Ship() {
   this->addChild(osgDB::readNodeFile(fileLocation));
}

