#ifndef PH_SUN_H
#define PH_SUN_H

#include <osg/LightSource>
#include <osg/Material>

#include "Sphere.h"

using namespace osg;

namespace ph {
    class Sun : public Group {
        private:
            ref_ptr<Light> light;
            ref_ptr<LightSource> source;
            ref_ptr<Material> material;
            ref_ptr<Sphere> sphere;
            
            void createLight(int lightNumber);
        
        public:
            Sun(const double radius, const int lsteps, const int wsteps, const int lightNumber);
    };
}

#endif
