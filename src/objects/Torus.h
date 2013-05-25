#ifndef PH_TORUS_H
#define PH_TORUS_H

#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

namespace ph {
    class Torus : public Geode {
        public:
            enum Style {NORMAL, FLAT};
            Torus(const double iRadius, const double tRadius, const int phiIteration, const int thetaIteration);
            void setStyle(const Style style);
            ~Torus();
        
        private:          
            double iRadius; // inner radius from origin to the object
            double tRadius; // radius of the torus-circle
            int phiIteration;
            int thetaIteration; // number of iterations for angle phi and theta
            //phi: angle of the torus-circle; theta: angle of the circle through the torus
            ref_ptr<Geometry> torus;
            Style style; // enum for normal or flat torus

            void compute();
            void setCoordinates();
            void setIndicies();
            Vec3d calculateVertex(const double theta, const double phi);
            Vec3d calculateNormal(const double theta, const double phi);
    };

    class FlatTorus : public Torus {
        public:
            FlatTorus(const double iRadius, const double tRadius, const int phiIteration, const int thetaIteration);
    };
}

#endif
