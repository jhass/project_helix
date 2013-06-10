#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>

#include "objects/Sphere.h"

osg::AnimationPath* createAnimationPath( float radius, float time )
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::LOOP );
    
    unsigned int numSamples = 32;
    float delta_yaw = 2*PI/time;
    float delta_time = time / (float)numSamples;
    for ( unsigned int i=0; i<numSamples; ++i )
    {
        float yaw = delta_yaw * (float)i;
        osg::Vec3 pos( 0.0, 0.0, 0.0f );
        osg::Quat rot( -yaw, osg::Z_AXIS );
        path->insert( delta_time * (float)i, osg::AnimationPath::ControlPoint(pos,rot) );
    }
    return path.release();    
}

int main(void) {
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200);
    ref_ptr<MatrixTransform> root = new MatrixTransform;

    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    root->addChild(sphere.get());
    
    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath( createAnimationPath(50.0f, 60.0f) );
    root->setUpdateCallback( apcb.get() );

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
