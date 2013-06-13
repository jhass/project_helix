#ifndef PH_UTIL_H

#include <osg/Vec3>
#include <osg/Array>
#include <osg/PrimitiveSet>
#include <osg/PositionAttitudeTransform>

using namespace osg;

namespace ph {
    Vec3f* computeNormal(Vec3f a, Vec3f b, Vec3f c);
    ref_ptr<Vec3Array> buildNormals(Vec3Array* vertices, DrawElementsUInt* indices);
    PositionAttitudeTransform* getDebugAxes(double scale, double dx, double dy, double dz);
    
    enum AnimationMode {LOOP, SWING};
    enum RotationAxis {POS_X_AXIS, POS_Y_AXIS, POS_Z_AXIS, NEG_X_AXIS, NEG_Y_AXIS, NEG_Z_AXIS};
    
    double sin_f(const double factor, double x);
    double cos_f(const double factor, double x);
    double lin_f(const double factor, double x);
    double quad_f(const double factor, double x);
    double pot_f(const double factor, double x);
    AnimationPath* createAnimationPath( float time, float func,
                                       ph::AnimationMode mode, ph::RotationAxis rAxis,
                                       double (*f_x) (double,double), double fac_x,
                                       double (*f_y) (double,double), double fac_y,
                                       double (*f_z) (double,double), double fac_z);
}

#endif
