#include <cmath>

#include "torus.h"

ph::Torus::Torus(const double iRadius, const double tRadius, const int phiIteration, const int thetaIteration) {
    this->iRadius = iRadius; //radius from origin to the torus
    this->tRadius = tRadius; //radius of the torus
    this->phiIteration = phiIteration; //iterations for the torus-circle
    this->thetaIteration = thetaIteration; //iterations of the planar circle
    this->torus = new Geometry;
    this->addDrawable(this->torus.get());
    this->compute();
}

ph::Torus::~Torus() {
    this->torus.release();
}

void ph::Torus::compute() {
    this->setCoordinates();
    this->setIndicies();
}

void ph::Torus::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;
    
    double phiStep = this->iRadius / phiIteration;
    double thetaStep = this->tRadius / thetaIteration;
    Vec3d coords;
    
    for (double i = 0, theta = 0; i <= this->phiIteration; i++, theta += thetaStep) {
        for (double j = 0, phi = 0; j <= this->thetaIteration; j++, phi += phiStep) {
            coords = Vec3d(
                (this->iRadius + this->tRadius* cos(2*PI*phi))* cos(2*PI*theta), // x
                (this->iRadius + this->tRadius* cos(2*PI*phi))* sin(2*PI*theta), // y
                this->tRadius* sin(2*PI*phi)//0.5* sin(2*PI*phi)              // z
                /*normally: this->tRadius* sin(2*PI*phi), but we need the other notation for 
                            our rings*/
            );
            texcoords->push_back(Vec2(theta, phi));
            vertices->push_back(coords);
            coords = Vec3d(
                (this->tRadius* cos(2*PI*phi))* cos(2*PI*theta), // x
                (this->tRadius* cos(2*PI*phi))* sin(2*PI*theta), // y
                this->tRadius* sin(2*PI*phi)             // z
            );
            coords.normalize();
            normals->push_back(coords);
        }
    }
    this->torus->setVertexArray(vertices.get());
    this->torus->setNormalArray(normals.get());
    this->torus->setTexCoordArray(0, texcoords.get());
    this->torus->setNormalBinding(Geometry::BIND_PER_VERTEX);
}

void ph::Torus::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->phiIteration; i++) {
        for (int j = 0; j <= this->thetaIteration; j++) {
            indices->push_back(i*(this->thetaIteration+1)+j);
            indices->push_back((i+1)*(this->thetaIteration+1)+j);
        }
        indices->push_back((i+1)*(this->thetaIteration+1)+this->thetaIteration);
        indices->push_back((i+1)*(this->thetaIteration+1));
    }
    
    this->torus->addPrimitiveSet(indices.get());
}
