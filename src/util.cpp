#include <osgDB/ReadFile>

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


PositionAttitudeTransform* ph::getDebugAxes(double scale, double dx, double dy, double dz) {
    ref_ptr<PositionAttitudeTransform> axes = new PositionAttitudeTransform;
    axes->setScale(Vec3d(scale, scale, scale));
    axes->setPosition(Vec3d(dx, dy, dz));
    axes->addChild(osgDB::readNodeFile("../resources/axes.osgt"));
    return axes.release();
}

// Funktionszeiger für gängige Funktionstypen

// f(x)= factor* sin(x)
double ph::sin_f(const double factor, double x) {
	return factor* sinf(x);
}

// f(x)= factor* cos(x)
double ph::cos_f(const double factor, double x) {
	return factor* cosf(x);
}

// f(x)= factor* x
double ph::lin_f(const double factor, double x) {
    return factor* x;
}

// f(x)= x^factor
double ph::quad_f(const double factor, double x) {
    return pow(x, factor);
}    

// Erstellt einen Animationspfad
/* create AnimationPath(Zeit, Funktion für rotation,
                        Funktion zur Bewegung in x, Funktionsfaktor in x,
                        Funktion zur Bewegung in y, Funktionsfaktor in y,
                        Funktion zur Bewegung in z, Funktionsfaktor in z)*/
osg::AnimationPath* ph::createAnimationPath( float time, float func, 
                                       double (*f_x) (double,double), double fac_x,
                                       double (*f_y) (double,double), double fac_y,
                                       double (*f_z) (double,double), double fac_z) {
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::LOOP );
    
    unsigned int numSamples = (int)time;
    float delta_rot = func/time;    
    
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( (float)f_x(fac_x,yaw), (float)f_y(fac_y,yaw), (float)f_z(fac_z,yaw) );
        osg::Quat rot( yaw, osg::Z_AXIS );
        path->insert( (float)i, osg::AnimationPath::ControlPoint(pos,rot) );
    }
    return path.release();    
}
