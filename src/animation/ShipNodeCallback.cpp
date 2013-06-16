#include <cmath>

#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/Quat>

#include "ShipNodeCallback.h"

using namespace std;

Vec3d ph::ShipNodeCallback::direction = Vec3d(0.3,0,0);
double ph::ShipNodeCallback::pitch = 0;
double ph::ShipNodeCallback::yaw = 0;
double ph::ShipNodeCallback::roll = 0;



void ph::ShipNodeCallback::operator()(Node* node, NodeVisitor* nv) {
	ref_ptr<ph::Ship> shipNode = dynamic_cast<ph::Ship*>(node); //You don't want the long way.

	//Rotate direction for translation
	Quat q = Quat(roll, Vec3d(1,0,0), pitch, Vec3d(0,1,0), yaw, Vec3d(0,0,1));
	direction = q * direction;

	//Rotate Ship
	Matrix rotation = shipNode->rotate->getMatrix();
	rotation = rotation * Matrix::rotate(q);
	shipNode->rotate->setMatrix(rotation);
	
	//Translate Ship
	Matrix translation = Matrix::translate(shipNode->translate->getMatrix().getTrans() + direction);
	shipNode->translate->setMatrix(translation);
	traverse(node, nv);
	pitch = yaw = roll = 0;
}

void ph::ShipNodeCallback::yawLeft() {
	yaw = (yaw + PI/30);
}

void ph::ShipNodeCallback::yawRight() {
	yaw = (yaw - PI/30);
}