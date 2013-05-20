#ifndef TORUS_H
#define TORUS_H

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

namespace ph {
    class Torus : public Geode {
        private:          
        	double iRadius;
			double oRadius;
			int phiIteration;
			int thetaIteration;          
			ref_ptr<Geometry> torus;

          void compute();
          void setCoordinates();
          void setIndicies();
          
        public:
            Torus(const double iRadius, const double oRadius, const int phiIteration, const int thetaIteration);
            ~Torus();
    };
}

#endif
