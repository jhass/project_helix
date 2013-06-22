#include <osg/MatrixTransform>

#include "MissileNodeCallback.h"
#include "objects/Missile.h"

ph::MissileNodeCallback::MissileNodeCallback(Vec3d& _direction, double _speed){
    direction = _direction;
    speed = _speed;
}

void ph::MissileNodeCallback::operator()(Node* node, NodeVisitor* nv) {
    ref_ptr<ph::Missile> missileNode = dynamic_cast<ph::Missile*>(node); //Casting to access the transformation nodes
    //Translate Missile by adding the direction vector
    Matrix translation = Matrix::translate(missileNode->translate->getMatrix().getTrans() + direction*speed);
    missileNode->translate->setMatrix(translation);
    traverse(node, nv);
}