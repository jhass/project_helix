#include <osgDB/ReadFile>

#include "Chronos.h"

using namespace osg;

// objectpath
string ph::Chronos::fileLocation = "../resources/chronos_station.obj";

ph::Chronos::Chronos() {
    this->station = osgDB::readNodeFile(this->fileLocation);
    this->addChild(this->station.get());
}
