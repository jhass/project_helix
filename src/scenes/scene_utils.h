#ifndef PH_SCENE_UTIL_H
#define PH_SCENE_UTIL_H

#include <osg/MatrixTransform>
#include "objects/Skybox.h"

using namespace osg;

namespace ph {
    enum ShipType {TURIAN, STATION, REAPER};

    ph::Skybox* createSkybox();
    MatrixTransform* createPlanet();
    MatrixTransform* createShip(ShipType type, double x, double y, double z);
    MatrixTransform* createAsteroidField(double x, double y, double z);
}

#endif
