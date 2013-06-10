#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include "objects/Fins.h"
#include "objects/Rotator.h"
#include <osg/MatrixTransform>
#include <osg/Math>
int main(void) {
    ref_ptr<ph::Rotator> rotator = new ph::Rotator(-300, 408, 30);
    rotator->setTexture(0, "../Textures/rotator_tx.png");
    
    ref_ptr<ph::Fins> fins1 = new ph::Fins(0,80);
    fins1->setTexture(0, "../Textures/fin.png");
    ref_ptr<ph::Fins> fins2 = new ph::Fins(0,60); 
    fins2->setTexture(0, "../Textures/fin.png");
    
    osg::ref_ptr<osg::MatrixTransform> transf = new osg::MatrixTransform;
    transf->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(-200.0f, 0.0f, 0.0f)));
    transf->addChild(fins1.get());
  
    osg::ref_ptr<osg::MatrixTransform> transf2 = new osg::MatrixTransform;
    transf2->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(200.0f, 0.0f, 0.0f)));
    transf2->addChild(fins2.get());
    
     	     
    ref_ptr<Group> root = new Group();
    root->addChild(rotator.get());
    root->addChild(transf.get());
    root->addChild(transf2.get());
    
    
    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
     //pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
