#include <osgDB/ReadFile>
#include <osg/Geode>

#include "Reaper.h"

using namespace osg;

//Objekt-Dateipfad angeben
std::string ph::Reaper::fileLocation = "../resources/reaper.obj";

ph::Reaper::Reaper() {
    this->reaper = osgDB::readNodeFile(this->fileLocation);
    this->addChild(this->reaper.get());
}
