#include <osg/MatrixTransform>


#include <osgGA/StateSetManipulator>



#include <osgParticle/AccelOperator>


#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <iostream>


#include "util.h"
#include "scene_utils.h"
#include "objects/Skybox.h"
#include "objects/Sun.h"
#include "objects/Torus.h"
#include "objects/Ship.h"
#include "objects/Chronos.h"
#include "objects/Reaper.h"
#include "objects/Asteroid.h"


// Creates the flight path of our turian spacecraft
AnimationPath* ph::createReaperFlightPath(double start_x, double end_x,
                                          double start_y, double end_y,
                                          double start_z, double end_z) {
    
    ref_ptr<AnimationPath> path = new AnimationPath;
    path->setLoopMode( osg::AnimationPath::LOOP);//NO_LOOPING );
    
    double start_time = 15.0;
    double rotation_time = 10.0;
    double return_time = 60.0;
    double new_x0 = 0, new_y0 = 0, new_z0 = 0;
    double dx = end_x - start_x;
    double dy = end_y - start_y;
    double dz = end_z - start_z;
    double time;
    
    unsigned int numSamples = (int)start_time;
    
    // Iterationsschritte bestimmen
    float delta_rot = 3*PI_2/(4*rotation_time); // Rotation um func in time
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
    AnimationPath::ControlPoint* cp = new AnimationPath::ControlPoint;
    
    // Pfad für die Rotation zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( new_x0, new_y0, new_z0 );
        Quat rot(yaw, Vec3(0, 1, 0));
        *cp = AnimationPath::ControlPoint(pos,rot);
        path->insert( (float)(time+i), *cp);
    }
    time += rotation_time;
    
    
    /* This still does not work ...
    // Pfad für die Rotation zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float yaw = delta_rot * (float)i;
        Vec3 pos( cp->getPosition() );
        Quat rot(yaw, Vec3(0, 1, 0));
        path->insert( (float)(time+i), AnimationPath::ControlPoint(pos,cp->getRotation()-rot) );
    }
    delta_pos = 1 / return_time;
    numSamples = (int) return_time;
    dx= new_x0; dy= new_y0;
    
    // Pfad für den Rückweg zusammensetzen
    for ( unsigned int i=0; i<=numSamples; ++i )
    {
        float d_pos = delta_pos * (float)i;
        new_x0 = (float)lin_f(-return_distance_x,d_pos,0);
        new_y0 = (float)lin_f(-return_distance_x/2,d_pos,0);
        Vec3 pos( new_x0, new_y0, 0 );
        Quat rot(3*PI/4, Vec3(0.0, 0.0, -1.0));
        //path->insert( (float)(start_time+rotation_time+i), AnimationPath::ControlPoint(pos,rot) );
    }*/
    
    return path.release();
 }
