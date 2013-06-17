#ifndef PH_SCENE_UTIL_H
#define PH_SCENE_UTIL_H

#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osgParticle/ParticleSystem>

#include "objects/Skybox.h"

using namespace osg;
using namespace osgParticle;

namespace ph {
    enum ShipType {TURIAN, STATION, REAPER};

    ph::Skybox* createSkybox(int lenght, int width);
    
    MatrixTransform* createPlanet(double x, double y, double z);
    MatrixTransform* createShip(ShipType type, double x, double y, double z);
    MatrixTransform* createAsteroidField(double x, double y, double z);
    
    AnimationPath* createTurianFlightPath(double x0, double y0, double z0);
    
    Group* createComet(double x, double y, double z); 
    ParticleSystem* createParticleSystem(Group* _parent);
}

#endif
