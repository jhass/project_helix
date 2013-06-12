#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include "objects/Fins.h"
#include "objects/Rotator.h"
#include <osg/MatrixTransform>
#include <osg/Math>
#include <osg/LightModel>



int main(void) {
    ref_ptr<ph::Rotator> rotator = new ph::Rotator(-300, 408, 30);
    rotator->setTexture(0, "../Textures/rotator_tx.png");
    
    ref_ptr<ph::Fins> fins1a = new ph::Fins(0,60);
    fins1a->setTexture(0, "../Textures/fin.png");
    
   
    osg::ref_ptr<osg::MatrixTransform> transf1b = new osg::MatrixTransform;
    transf1b->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0), 1, 0, 0));
    transf1b->addChild(fins1a.get());
    
   
    osg::ref_ptr<osg::MatrixTransform> transf1c = new osg::MatrixTransform;
    transf1c->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 1, 0, 0));
    transf1c->addChild(fins1a.get());
    
  
    osg::ref_ptr<osg::MatrixTransform> transf1d = new osg::MatrixTransform;
    transf1d->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(-90.0), 1, 0, 0));
    transf1d->addChild(fins1a.get());
    
    ref_ptr<Group> fins1 = new Group();
    fins1->addChild(fins1a.get());
    fins1->addChild(transf1b.get());
    fins1->addChild(transf1c.get());
    fins1->addChild(transf1d.get());

    
    osg::ref_ptr<osg::MatrixTransform> transf = new osg::MatrixTransform;
    transf->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(-180.0f, 0.0f, 0.0f)));
    transf->addChild(fins1.get());
  
    osg::ref_ptr<osg::MatrixTransform> transf2 = new osg::MatrixTransform;
    transf2->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0), 0, 1, 0)*(osg::Matrix::translate(220.0f, 0.0f, 0.0f))*(osg::Matrix::scale(0.8f,0.8f,0.8f)));
    transf2->addChild(fins1.get());
    
     	     
    
  
    ref_ptr<LightModel> lm = new LightModel;
    lm->setTwoSided(true);
    fins1->getOrCreateStateSet()->setAttributeAndModes(lm.get());
    
    ref_ptr<Group> root = new Group();
    root->addChild(rotator.get());
    root->addChild(transf.get());
    root->addChild(transf2.get());
  
    
  

    // wenn man die Dreiecke mal sehen will:
     ref_ptr<PolygonMode> pm = new PolygonMode;
    // pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
     root->getOrCreateStateSet()->setAttribute(pm.get());
 
    
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
