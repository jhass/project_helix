#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>


#include "objects/Sphere.h"
#include "objects/Torus.h"
#include "util.h"

using namespace osg;

int main(void) {
    // Sphere(radius, Steps)
    ref_ptr<ph::Sphere> sphere = new ph::Sphere(5, 200);
    ref_ptr<MatrixTransform> planet = new MatrixTransform;
    ref_ptr<MatrixTransform> attitude = new MatrixTransform;
    ref_ptr<Group> root = new Group();

    // giving the sphere a texturefile
    sphere->setTexture(0, "../resources/EarthMap.jpg");
    
    // Torus(innerRadius, torusRadius, lengthSteps, widthSteps)
    ref_ptr<ph::Torus> torus = new ph::Torus(8, 1.5, 100);

    // Default ist NORMAL
    torus->setStyle(ph::Torus::FLAT);
    torus->setTexture(0, "../resources/rings.jpg");
    
    planet->addChild(sphere.get());
    planet->addChild(torus.get());
    
    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath( ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Z_AXIS,
     ph::sin_f, 5, 0, ph::cos_f, 5, 0, ph::lin_f, -20, 0));
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
