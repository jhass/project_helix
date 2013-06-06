#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>

#include "objects/Sphere.h"
#include "objects/Torus.h"

osg::AnimationPath* createAnimationPath( float radius, float time )
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::LOOP );
    
    unsigned int numSamples = (int)time;
    float delta_yaw = 2*PI/time;
    float delta_time = time / (float)numSamples;
    for ( unsigned int i=0; i<=numSamples; ++i )
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
    ref_ptr<MatrixTransform> planet = new MatrixTransform;
    ref_ptr<MatrixTransform> attitude = new MatrixTransform;
    ref_ptr<Group> root = new Group();

    // giving the sphere a texturefile
    sphere->setTexture(0, "../Textures/EarthMap.jpg");
    
    // Torus(innerRadius, torusRadius, lengthSteps, widthSteps)
    ref_ptr<ph::Torus> torus = new ph::Torus(8, 1.5, 100);

    // Default ist NORMAL
    torus->setStyle(ph::Torus::FLAT);
    
    planet->addChild(sphere.get());
    planet->addChild(torus.get());
    
    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath( createAnimationPath(5.0f, 60.0f) );
    planet->setUpdateCallback( apcb.get() );

    // enables PolygonMode
     ref_ptr<PolygonMode> pm = new PolygonMode;
     pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    // planet->getOrCreateStateSet()->setAttribute(pm.get());
    
    attitude->setMatrix( Matrix::rotate(PI/4,Vec3(1.0,0.0,1.0)));
    attitude->addChild( planet.get());
    
    osgViewer::Viewer viewer;
    viewer.setSceneData(attitude.get());
    return viewer.run();
}
