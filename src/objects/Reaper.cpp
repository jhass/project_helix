#include <osgDB/ReadFile>
#include <osg/Geode>

#include "util.h"

#include "Reaper.h"

using namespace osg;

//Objekt-Dateipfad angeben
std::string ph::Reaper::fileLocation = "../resources/reaper.obj";

ph::Reaper::Reaper() {
    this->transform = new MatrixTransform;
    this->transform->addChild(osgDB::readNodeFile(this->fileLocation));
    this->addChild(this->transform.get());
}

void ph::Reaper::transformAndAnimate(const Matrix& matrix,
                                     double start_x, double mid_x, double end_x,
                                     double start_y, double mid_y, double end_y,
                                     double start_z, double mid_z, double end_z) {
    this->transform->setMatrix(matrix);
    ref_ptr<AnimationPathCallback> animation = new osg::AnimationPathCallback;
    animation->setAnimationPath(createFlightPath(start_x, mid_x, end_x,
                                                 start_y, mid_y, end_y,
                                                 start_z, mid_z, end_z));
    this->setUpdateCallback(animation.get());
}

AnimationPath* ph::Reaper::createFlightPath(double start_x, double mid_x, double end_x,
                                     double start_y, double mid_y, double end_y,
                                     double start_z, double mid_z, double end_z) {
    
    ref_ptr<AnimationPath> path = new AnimationPath;
    path->setLoopMode( osg::AnimationPath::NO_LOOPING );
    
    double time_speed = 1; // for illustrational use only
    double start_time = 300.0/ time_speed;
    double rotation_time = 10.0/ time_speed;
    double wait_time = 15.0/ time_speed;
    double return_time = 300.0/ time_speed;
    double new_x0 = 0, new_y0 = 0, new_z0 = 0;
    double dx = mid_x - start_x;
    double dy = mid_y - start_y;
    double dz = mid_z - start_z;
    double time;
    
    unsigned int numSamples = (int)start_time;
    
    // Iterationsschritte bestimmen
    float rot_angle = 3*PI_2/4;
    float delta_rot = rot_angle/rotation_time; // Rotation um func in time
    float delta_pos = 1 / start_time; // Bewegung um factor* func in time
 
    // Pfad für ersten Teilweg zusammensetzen   
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float d_pos = delta_pos * (float)i;
        new_x0 = (float)lin_f(dx,d_pos,start_x);
        new_y0 = (float)lin_f(dy,d_pos,start_y);
        new_z0 = (float)lin_f(dz,d_pos,start_z);
        Vec3 pos( new_x0, new_y0, new_z0 );
        path->insert( (float)i, AnimationPath::ControlPoint(pos) );
    }
    
    numSamples = (int) rotation_time;
    time = start_time;
    
    // Rotate to fire position
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(yaw, Vec3(0, 1, 0));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,rot));
    }
    time += rotation_time;

    // Wait
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(rot_angle, Vec3(0, 1, 0));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,rot));
    }  
    time += wait_time;  

    // Return to previous position
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(rot_angle-yaw, Vec3(0, 1, 0));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,rot) );
    }
    time +=rotation_time;
    rot_angle = PI/8;
    delta_rot = rot_angle/rotation_time;
    
    // Rotate to new position
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(yaw, Vec3(0, 0, 1));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,rot));
    }
    
    time += rotation_time;
    delta_pos = 1 / return_time;
    numSamples = (int) return_time;
    dx = end_x - mid_x;
    dy = end_y - mid_y;
    dz = end_z - mid_z;
    
    // Pfad für den Rückweg zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float d_pos = delta_pos * (float)i;
        new_x0 = (float)lin_f(dx,d_pos,mid_x);
        new_y0 = (float)lin_f(dy,d_pos,mid_y);
        new_z0 = (float)lin_f(dz,d_pos,mid_z);
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(rot_angle, Vec3(0,0,1));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,rot) );
    }
    
    return path.release();
 }

