#ifndef PH_COMET_H
#define PH_COMET_H

#include "osgParticle/ParticleSystem"
#include <osg/MatrixTransform>
#include <osg/Group>

#include "Asteroid.h"

using namespace osgParticle;
using namespace osg;

namespace ph {
    class Comet : public Group {
        private:
            ParticleSystem* createParticleSystem(Group* parent);
            ref_ptr<MatrixTransform> particleSystem;
            ref_ptr<ph::Asteroid> asteroid;
        public:
            Comet(const double radius, const int lsteps, const int wsteps, 
                  const int xd, const int yd, const int zd);
            void translateAndAnimate(double x, double y, double z);
    };
}

#endif
