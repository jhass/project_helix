#include <osg/Matrix>
#include <osg/Quat>

#include "objects/Ship.h"
#include "objects/Missile.h"

#include "ShipNodeCallback.h"


using namespace std;

bool isDead(const ref_ptr<ph::Missile>& m) {return m->lifetime < 1; }

ph::ShipNodeCallback::ShipNodeCallback() {
    direction = Vec3d(0.3,0,0);
    up        = Vec3d(0,0,1);
    x_axis    = Vec3d(1,0,0);
    y_axis    = Vec3d(0,1,0);
    z_axis    = Vec3d(0,0,1);
    speed = 1;
    pitch = 0;
    yaw   = 0;
    roll  = 0;
    missilefired = false;
}


void ph::ShipNodeCallback::operator()(Node* node, NodeVisitor* nv) {
    ref_ptr<ph::Ship> shipNode = dynamic_cast<ph::Ship*>(node); //Casting to access the transformation nodes

    
    Quat q = Quat(roll, x_axis, pitch, y_axis, yaw, z_axis); // Quaternion(?) for Rotation
    direction = q * direction; //Rotate direction vector for translation
    up = q * up; //Rotate the up-vector of the camera

    //Rotate ship
    Matrix rotation = shipNode->rotate->getMatrix();
    rotation = rotation * Matrix::rotate(q);
    shipNode->rotate->setMatrix(rotation);
    
    //Translate ship by adding the direction vector
    Matrix translation = Matrix::translate(shipNode->translate->getMatrix().getTrans() + direction*speed);
    shipNode->translate->setMatrix(translation);

    // Update camera
    Vec3d eye = translation.getTrans()+up;
    shipNode->camera->setViewMatrixAsLookAt(
         eye,            // eye
         eye+direction,  // center
         up              // up
    );

    //Rotating the axis of the quat, so further rotations are correct
    x_axis = q * x_axis;
    y_axis = q * y_axis;
    z_axis = q * z_axis;

    //Resetting the angles so the ship flies straight unless a button is pressed
    pitch = yaw = roll = 0;
    
    if (missilefired) {
        shipNode->fireMissile(direction, speed*1.5); //set speed here
        missilefired = false;
    }

    for (list< ref_ptr<Missile> >::iterator it=shipNode->missiles.begin(); it != shipNode->missiles.end(); it++) {
        (*it)->lifetime--;
        if ((*it)->lifetime == 0) shipNode->removeChild((*it));
    }

    shipNode->missiles.remove_if(isDead);

    traverse(node, nv);
}

void ph::ShipNodeCallback::yawLeft() {
    yaw +=  PI/60;
}

void ph::ShipNodeCallback::yawRight() {
    yaw -= PI/60;
}

void ph::ShipNodeCallback::pitchUp() {
    pitch -= PI/60;
}

void ph::ShipNodeCallback::pitchDown() {
    pitch +=  PI/60;
}

void ph::ShipNodeCallback::rollRight() {
    roll +=  PI/60;
}

void ph::ShipNodeCallback::rollLeft() {
    roll -=  PI/60;
}

void ph::ShipNodeCallback::turboOn() {
    speed = 160;
}

void ph::ShipNodeCallback::turboOff() {
    speed = 1;
}

void ph::ShipNodeCallback::fireMissile() {
    missilefired = true;
}