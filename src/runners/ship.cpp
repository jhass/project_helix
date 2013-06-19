#include <osgViewer/Viewer>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>

#include "objects/Ship.h"
#include "animation/ShipNodeCallback.h"

using namespace osgViewer;

/*osg::AnimationPath* createAnimationPath( float radius, float time )
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode( osg::AnimationPath::LOOP );
    
    unsigned int numSamples = 32;
    float delta_yaw = 2.0f;
    float delta_time = time / (float)numSamples;
    for ( unsigned int i=0; i<numSamples; ++i )
    {
        float yaw = delta_yaw * (float)i;
        //osg::Vec3 pos( sinf(yaw)*radius, cosf(yaw)*radius, 0.0f );
        osg::Vec3 pos( yaw, 0.0, 0.0f );
        //osg::Quat rot( -yaw, osg::Z_AXIS );
        path->insert( delta_time * (float)i, osg::AnimationPath::ControlPoint(pos) );
    }
    return path.release();    
} */

int main(void) {
    ref_ptr<ph::Ship> ship = new ph::Ship;
    Viewer viewer;
    
    
    //osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
    //root->addChild( ship.get() );
    
    //osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    //apcb->setAnimationPath( createAnimationPath(50.0f, 6.0f) );
    //root->setUpdateCallback( apcb.get() );
    // ship->setUpdateCallback(new ph::ShipNodeCallback);
    
    viewer.setSceneData(ship.get());
    return viewer.run();
}
