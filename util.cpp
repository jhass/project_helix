#include "util.h"


Vec3f* ph::computeNormal(Vec3f a, Vec3f b, Vec3f c) {
    Vec3f* r = new Vec3f;
    r->set((b-a)^(c-a));
    r->normalize();
    return r;
}

ref_ptr<Vec3Array> ph::buildNormals(ref_ptr<Vec3Array> vertices, ref_ptr<DrawElementsUInt> indices) {
    ref_ptr<Vec3Array> normals = new Vec3Array(indices->size()/3);
    Vec3f* normal;
  
    for (int i = 0; i < indices->size(); i += 3) {
        normal = computeNormal((*vertices)[(*indices)[i]],
                               (*vertices)[(*indices)[i+1]],
                               (*vertices)[(*indices)[i+2]]);
        (*normals)[i/3].set(*normal);
        delete normal;
    }

    vertices.release();
    indices.release();
    return normals.release();
}
