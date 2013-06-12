#include <osgDB/ReadFile>
#include <osg/Geode>

#include "Chronos.h"

using namespace osg;

//Objekt-Dateipfad angeben
std::string ph::Chronos::fileLocation = "../resources/chronos_station.obj";

ph::Chronos::Chronos() {
    this->station = osgDB::readNodeFile(this->fileLocation);
    this->addChild(this->station.get());
}
