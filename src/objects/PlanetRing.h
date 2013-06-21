#ifndef PH_PLANET_RING_H
#define PH_PLANET_RING_H

#include "Torus.h"

namespace ph {
    class PlanetRing : public Torus {
        private:
            void setRingTexture();
        public:
            PlanetRing(const double iRadius, const double tRadius, const int iteration);
    };
}

#endif
