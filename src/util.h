#ifndef PH_UTIL_H

#include <osg/ref_ptr>
#include <osg/Vec3f>
#include <osg/Array>
#include <osg/PrimitiveSet>
#include <osg/PositionAttitudeTransform>

using namespace osg;

namespace ph {
    Vec3f* computeNormal(Vec3f a, Vec3f b, Vec3f c);
    ref_ptr<Vec3Array> buildNormals(ref_ptr<Vec3Array> vertices, ref_ptr<DrawElementsUInt> indices);
    PositionAttitudeTransform* getDebugAxes(double scale, double dx, double dy, double dz);
}

#endif
