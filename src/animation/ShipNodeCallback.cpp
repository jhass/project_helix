#include <cmath>

#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/Quat>

#include "ShipNodeCallback.h"

using namespace std;

Vec3d ph::ShipNodeCallback::direction = Vec3d(0.3,0,0);
Vec3d ph::ShipNodeCallback::up        = Vec3d(0,0,1);
Vec3d ph::ShipNodeCallback::x_axis    = Vec3d(1,0,0);
Vec3d ph::ShipNodeCallback::y_axis    = Vec3d(0,1,0);
Vec3d ph::ShipNodeCallback::z_axis    = Vec3d(0,0,1);
double ph::ShipNodeCallback::speed = 1;
double ph::ShipNodeCallback::pitch = 0;
double ph::ShipNodeCallback::yaw   = 0;
double ph::ShipNodeCallback::roll  = 0;



void ph::ShipNodeCallback::operator()(Node* node, NodeVisitor* nv) {
	ref_ptr<ph::Ship> shipNode = dynamic_cast<ph::Ship*>(node); //You don't want the long way.

	//Rotate direction for translation
	Quat q = Quat(roll, x_axis, pitch, y_axis, yaw, z_axis);
	direction = q * direction;
	up = q * up;

	//Rotate Ship
	Matrix rotation = shipNode->rotate->getMatrix();
	rotation = rotation * Matrix::rotate(q);
	shipNode->rotate->setMatrix(rotation);
	
	//Translate Ship
	Matrix translation = Matrix::translate(shipNode->translate->getMatrix().getTrans() + direction*speed);
	shipNode->translate->setMatrix(translation);

	// Update camera
	Vec3d eye = translation.getTrans()+up;
	shipNode->camera->setViewMatrixAsLookAt(
		 eye,            // eye
         eye+direction,  // center
         up              // up
    );

    x_axis = q * x_axis;
    y_axis = q * y_axis;
    z_axis = q * z_axis;
	pitch = yaw = roll = 0;
	
	traverse(node, nv);
}

void ph::ShipNodeCallback::yawLeft() {
	yaw +=  PI/60;
}

void ph::ShipNodeCallback::yawRight() {
	yaw -= PI/60;
}

void ph::ShipNodeCallback::pitchUp() {
	pitch += PI/60;
}

void ph::ShipNodeCallback::pitchDown() {
	pitch -=  PI/60;
}

void ph::ShipNodeCallback::turboOn() {
	speed = 160;
}

void ph::ShipNodeCallback::turboOff() {
	speed = 1;
}
