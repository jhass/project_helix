#ifndef PH_REAPER_H
#define PH_REAPER_H

#include <string>

#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/AnimationPath>

using namespace osg;

namespace ph {
    class Reaper : public Group {
        private:
            static std::string fileLocation;

        public: 
            ref_ptr<MatrixTransform> transform;
            Reaper();
            AnimationPath* createFlightPath(double start_x, double end_x,
                             double start_y, double end_y,
                             double start_z, double end_z);
            void transformAndAnimate(const Matrix& matrix,
                                     double start_x, double end_x,
                                     double start_y, double end_y,
                                     double start_z, double end_z);
    };
}
#endif
