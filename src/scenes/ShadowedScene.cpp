#include <osgShadow/ShadowMap>
#include <osgShadow/ShadowedScene>

#include "ShadowedScene.h"

using namespace osg;

ph::ShadowedScene::ShadowedScene() : MainScene() {
    shadowedScene = new osgShadow::ShadowedScene;
    ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
    sm->setAmbientBias(Vec2(0.5,1));
    shadowedScene->setShadowTechnique(sm.get());
    shadowedScene->addChild(dynamic_cast<Node*>(this->clone(CopyOp::SHALLOW_COPY)));
    this->removeChildren(0, this->getNumChildren());
    this->addChild(shadowedScene);
}
