#ifndef PH_SCENE_UTIL_H
#define PH_SCENE_UTIL_H

#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osgParticle/ParticleSystem>

#include "objects/Skybox.h"

using namespace osg;
using namespace osgParticle;

namespace ph {

    AnimationPath* createReaperFlightPath(double start_x, double end_x,
                                          double start_y, double end_y,
                                          double start_z, double end_z);
}

#endif
