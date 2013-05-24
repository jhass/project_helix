#ifndef SUN_H
#define SUN_H

#include <osg/LightSource>

#include "sphere.h"

using namespace osg;

namespace ph {
	class Sun : public Sphere {
		private:
			ref_ptr<Light> light;
			ref_ptr<LightSource> source;
			
			void createLight(int lightNumber);
		
		public:
			Sun(const double radius, const int lsteps, const int wsteps, const int lightNumber);
			void setLight(ref_ptr<Group> &node);
            ~Sun();
	};
}

#endif
