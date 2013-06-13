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

// f(x)= factor* sin(x); mit 2*PI für Kreisbewegungen
double ph::sin_f(const double factor, double x) {
	return factor* sinf(2*PI*x);
}

// f(x)= factor* cos(x); mit 2*PI für Kreisbewegungen
double ph::cos_f(const double factor, double x) {
	return factor* cosf(2*PI*x);
}

// f(x)= factor* x
double ph::lin_f(const double factor, double x) {
    return factor* x;
}

// f(x)= x^factor
double ph::quad_f(const double factor, double x) {
    return pow(x, factor);
}  

// f(x)= factor^x
double ph::pot_f(const double factor, double x) {
    return pow(factor, x);
}  

// Erstellt einen Animationspfad
/* create AnimationPath(Zeit, Funktion für rotation,
                        Animationsmodus, Rotationsachse,
                        Funktion zur Bewegung in x, Funktionsfaktor in x,
                        Funktion zur Bewegung in y, Funktionsfaktor in y,
                        Funktion zur Bewegung in z, Funktionsfaktor in z)

   Soll in eine Richtung keine Translation durchgeführt werden, muss entsprechende
   Funktion mit NULL aufgerufen werden */
osg::AnimationPath* ph::createAnimationPath( float time, float func,
                                       ph::AnimationMode mode, ph::RotationAxis rAxis,
                                       double (*f_x) (double,double), double fac_x,
                                       double (*f_y) (double,double), double fac_y,
                                       double (*f_z) (double,double), double fac_z) {
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    
    // Default: Keine Translation in entsprechende Richtung
    if (f_x == NULL) {f_x = lin_f; fac_x = 0;}
    if (f_y == NULL) {f_y = lin_f; fac_y = 0;}
    if (f_z == NULL) {f_z = lin_f; fac_z = 0;}
    
    // Animationsmodus ermitteln
    switch (mode) {
    case LOOP: path->setLoopMode( osg::AnimationPath::LOOP ); break;
    case SWING: path->setLoopMode( osg::AnimationPath::SWING ); break;
    }
    
    // Rotationsachse festlegen
    Vec3 tAxis;
    switch (rAxis) {
    case POS_X_AXIS: tAxis = Vec3(1.0, 0.0, 0.0); break;
    case POS_Y_AXIS: tAxis = Vec3(0.0, 1.0, 0.0); break;
    case POS_Z_AXIS: tAxis = Vec3(0.0, 0.0, 1.0); break;
    case NEG_X_AXIS: tAxis = Vec3(-1.0, 0.0, 0.0); break;
    case NEG_Y_AXIS: tAxis = Vec3(0.0, -1.0, 0.0); break;
    case NEG_Z_AXIS: tAxis = Vec3(0.0, 0.0, -1.0); break;
    }    
        
    unsigned int numSamples = (int)time;
    
    // Iterationsschritte bestimmen
    float delta_rot = func/time; // Rotation um func in time
    float delta_pos = 1 / time; // Bewegung um factor* func in time
 
    // Pfad zusammensetzen   
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        float d_pos = delta_pos * (float)i;
        Vec3 pos( (float)f_x(fac_x,d_pos), (float)f_y(fac_y,d_pos), (float)f_z(fac_z,d_pos) );
        osg::Quat rot(yaw, tAxis);
        path->insert( (float)i, osg::AnimationPath::ControlPoint(pos,rot) );
    }
    return path.release();    
}
