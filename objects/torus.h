#ifndef TORUS_H
#define TORUS_H

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
            double iRadius;
            double tRadius;
            int phiIteration;
            int thetaIteration;          
            ref_ptr<Geometry> torus;
            Style style;

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
