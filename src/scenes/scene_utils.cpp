#include <osg/MatrixTransform>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Material>
#include <osg/Point>
#include <osg/PointSprite>
#include <osgGA/StateSetManipulator>

#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RadialShooter>
#include <osg/BlendFunc>
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
 
// Creating particle system for Comet
ParticleSystem* ph::createParticleSystem(Group* _parent) {
    ref_ptr<Group> parent = _parent;
    ref_ptr<ParticleSystem> ps = new ParticleSystem();
    Particle* part = new Particle();
    part->setShape(Particle::POINT);
    part->setLifeTime(5);
    ps->setDefaultParticleTemplate(*part);
    
    ref_ptr<BlendFunc> blendFunc = new BlendFunc();
    blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create texture
    ref_ptr<Texture2D> texture = new Texture2D;

    texture->setImage( osgDB::readImageFile("../resources/particle.rgb") );
    
    // StateSetattribute setzen
    ref_ptr<StateSet> ss = ps->getOrCreateStateSet();
    ss->setAttributeAndModes(blendFunc.get());
    // Texture übergeben
    ss->setTextureAttributeAndModes(0, texture.get());
    // Point-Atrribut setzen
    ref_ptr<Point> attribute = new Point(6.0f);
    ss->setAttribute(attribute);
    ref_ptr<PointSprite> sprite = new PointSprite;
    ss->setTextureAttributeAndModes(0, sprite);
    // Lichteffekte auf Partikel ausmachen
    ss->setMode( GL_LIGHTING, StateAttribute::OFF);
    // Rendering einstellen
    ss->setRenderingHint( StateSet::TRANSPARENT_BIN );
    
    //Rng
    ref_ptr<RandomRateCounter> rrc = new RandomRateCounter();
    rrc->setRateRange( 500, 1000 );
    
    //makeshooter
    ref_ptr<RadialShooter> myshooter = new RadialShooter();
    myshooter->setThetaRange(-PI_2+PI_4/2,-PI_2-PI_4/2); // Streuung z-x-ebene gegen UZS
    myshooter->setPhiRange(PI_2-PI_4/2,PI_2+PI_4/2); //Streuung x-y-ebene gegen UZS
    myshooter->setInitialSpeedRange(5,20); //Geschwindigkeit
    
    //Emmiter
    ref_ptr<ModularEmitter> emitter = new ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter(myshooter.get());    
        
    //??
    ref_ptr<ModularProgram> program = new ModularProgram();
    program->setParticleSystem( ps.get() );

    
    //Rendering stuff2
    ref_ptr<Geode> geode = new Geode();
    geode->addDrawable( ps.get() );
    
    parent->addChild( emitter.get() );
    parent->addChild( program.get() );
    parent->addChild( geode.get() );
    return ps.release();
}

//creates 1d texture based on osgtexture1d code example
StateSet* ph::createTorusTexture(Geode* model) {
    Image* image = new Image;
    int pixels = 1000;
    
    // image anlegen mit pixels x 1 x 1 und RGBA dargestellt durch Vec4
    image->allocateImage(pixels,1,1,GL_RGBA,GL_FLOAT);
    image->setInternalTextureFormat(GL_RGBA);
    
    // creating colors
    vector<Vec4> colorBands;
    colorBands.push_back(Vec4(0.0,0.0,0.0,1.0));
    colorBands.push_back(Vec4(0.1,0.1,0.1,1.0));
    colorBands.push_back(Vec4(0.2,0.2,0.2,1.0));
    colorBands.push_back(Vec4(0.3,0.3,0.3,1.0));
    colorBands.push_back(Vec4(1.0,1.0,1.0,1.0));
    
    float band_size = colorBands.size();
    float delta = band_size / (float) pixels;
    int pos = 0, count = 0;
    
    /* creating image data (% Pixel; symmetrical)
       10 % dark grey; 3% black; 5% light grey;
       2% black; 10% light grey; 2% black;
       5% light grey; 3% black; 5% light grey
       5% dark grey*/
    Vec4* dataPoints = (Vec4*)image->data();
    for (int k=1; k <=2; k++) {
        for(int i=0; i<pixels/10; i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/10); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos+= count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[2];
            *dataPoints++ = color;
            count = i;
        }

        pos+= count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }  
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
       pos += count;
       for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
            count = i;
        }
        pos += count;
    }
    
    Texture1D* texture = new Texture1D;
    texture->setWrap(Texture1D::WRAP_T, Texture::MIRROR);
    texture->setFilter(Texture1D::MIN_FILTER, Texture::NEAREST);
    texture->setImage(image);
    
    Material* material = new Material;
    StateSet* stateSet = new StateSet;
    
    stateSet->setTextureAttribute(0,texture, StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_1D, StateAttribute::ON| StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_2D, StateAttribute::OFF| StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0,GL_TEXTURE_3D, StateAttribute::OFF| StateAttribute::OVERRIDE);
    
    stateSet->setAttribute(material, StateAttribute::OVERRIDE);
    material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.1,0.1,0.1,1.0));
    material->setAmbient(Material::FRONT_AND_BACK, Vec4(1,1,1,1.0));
    material->setSpecular(Material::FRONT_AND_BACK, Vec4(1,1,1,1));
    material->setShininess(Material::FRONT_AND_BACK, 30);
    
    return stateSet;
}


