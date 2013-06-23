#ifndef PH_SUN_H
#define PH_SUN_H

#include <string>

#include <osg/LightSource>
#include <osg/Material>

#include "Sphere.h"

using namespace osg;
using namespace std;

namespace ph {
    class Sun : public Group {
        private:
            ref_ptr<Light> light; // light- and sourceelement of the sun
            ref_ptr<Material> material; // material of the sphere
            ref_ptr<Sphere> sphere;
            double red;
            double blue;
            double green;
            
            void createLight(int lightNumber); // lightNumber: OpenGLLightNumber [0,7]
        
        public:
            Sun(const double radius, const int steps,
             const int lightNumber,const double red, const double blue, const double green);
            ref_ptr<LightSource> source;
            void setTexture(const int number, const string filename);
    };
}

#endif
