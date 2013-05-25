#include <cmath>

#include "Torus.h"

ph::Torus::Torus(const double iRadius, const double tRadius, const int phiIteration, const int thetaIteration) {
    this->iRadius = iRadius; //radius from origin to the torus
    this->tRadius = tRadius; //radius of the torus
    this->phiIteration = phiIteration; //iterations for the torus-circle
    this->thetaIteration = thetaIteration; //iterations of the planar circle

    this->style = NORMAL;
    this->torus = new Geometry;

    this->addDrawable(this->torus.get());
    this->compute();
}

ph::Torus::~Torus() {
    this->torus.release();
}

void ph::Torus::setStyle(const Style style) {
    this->style = style;
    this->compute();
}

void ph::Torus::compute() {
    this->setCoordinates();
    this->setIndicies();
}


void ph::Torus::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;
    
    double thetaStep = this->tRadius/thetaIteration;
    double phiStep = this->iRadius/phiIteration;
    double phi, theta;
    
    for (int i = 0; i <= this->phiIteration; i++) {
        for (int j = 0; j <= this->thetaIteration; j++) {
        	phi = (double) j / phiIteration;
        	theta = (double) i / thetaIteration;
            vertices->push_back(calculateVertex(theta, phi));
            normals->push_back(calculateNormal(theta, phi));
            texcoords->push_back(Vec2(theta, phi));
        }
    }
    
    this->torus->setVertexArray(vertices.get());
    this->torus->setNormalArray(normals.get());
    this->torus->setNormalBinding(Geometry::BIND_PER_VERTEX);
    this->torus->setTexCoordArray(0, texcoords.get());
}

Vec3d ph::Torus::calculateVertex(const double theta, const double phi) {
    double z = 0;

    if (this->style == FLAT) {
        z = 0.5* sin(2*PI*phi);
    } else if (this->style == NORMAL) {
        z =  this->tRadius* sin(2*PI*phi);
    }

	Vec3d coords = Vec3d(
        (this->iRadius + this->tRadius*cos(2*PI*phi))*cos(2*PI*theta), // x
        (this->iRadius + this->tRadius*cos(2*PI*phi))*sin(2*PI*theta), // y
        z // z
    );    
    return coords;
}

Vec3d ph::Torus::calculateNormal(const double theta, const double phi) {
    Vec3d coords = Vec3d(
        (this->tRadius* cos(2*PI*phi))* cos(2*PI*theta), // x
        (this->tRadius* cos(2*PI*phi))* sin(2*PI*theta), // y
         this->tRadius* sin(2*PI*phi)                    // z
    );

    coords.normalize();

    return coords;
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


ph::FlatTorus::FlatTorus(const double iRadius, const double tRadius, const int phiIteration, const int thetaIteration) : Torus(iRadius, tRadius, phiIteration, thetaIteration) {
    this->setStyle(FLAT);
}
