#ifndef PH_UTIL_H

#include <osg/ref_ptr>
#include <osg/Vec3f>
#include <osg/Array>
#include <osg/PrimitiveSet>
#include <osg/PositionAttitudeTransform>
#include <cmath>

using namespace osg;

namespace ph {
    Vec3f* computeNormal(Vec3f a, Vec3f b, Vec3f c);
    ref_ptr<Vec3Array> buildNormals(ref_ptr<Vec3Array> vertices, ref_ptr<DrawElementsUInt> indices);
    PositionAttitudeTransform* getDebugAxes(double scale, double dx, double dy, double dz);
    
    double sin_f(const double factor, double x);
    double cos_f(const double factor, double x);
    double lin_f(const double factor, double x);
    double quad_f(const double factor, double x);
    AnimationPath* createAnimationPath( float time, float func, 
                                       double (*f_x) (double,double), double fac_x,
                                       double (*f_y) (double,double), double fac_y,
                                       double (*f_z) (double,double), double fac_z);
}

#endif
