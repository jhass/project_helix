#include <cmath>

#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/Quat>

#include "ShipNodeCallback.h"

using namespace std;

Vec3d ph::ShipNodeCallback::direction = Vec3d(0.5,0,0);

void ph::ShipNodeCallback::operator()(Node* node, NodeVisitor* nv) {
	ref_ptr<ph::Ship> shipNode = dynamic_cast<ph::Ship*>(node); //You don't want the long way.

	//Rotate direction for translation
	Quat q = Quat(0, Vec3d(1,0,0), 0, Vec3d(0,1,0), PI/120, Vec3d(0,0,1));
	direction = q * direction;

	//Rotate Ship
	Matrix rotation = shipNode->rotate->getMatrix();
	rotation = rotation * Matrix::rotate(q);
	shipNode->rotate->setMatrix(rotation);
	
	//Translate Ship
	Matrix translation = Matrix::translate(shipNode->translate->getMatrix().getTrans() + direction);
	shipNode->translate->setMatrix(translation);
	traverse(node, nv);
}