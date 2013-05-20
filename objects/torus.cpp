#include <cmath>

#include "torus.h"

using namespace osg;

ph::Torus::Torus(const double iRadius, const double oRadius, const int phiIteration, const int thetaIteration) {
	this->iRadius = iRadius;
	this->oRadius = oRadius;
	this->phiIteration = phiIteration;
	this->thetaIteration = thetaIteration;
	this->torus = new Geometry;
	this->addDrawable(this->torus.get());
	this->compute();
}

ph:Torus::~Torus() {
	this->torus.release();
}

void ph::Torus::compute() {
    this->Coordinates();
    this->setIndicies();
}

void ph::Torus::setCoordinates() {
	ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
	ref_ptr<Vec2Array> texcoords = new Vec2Array;
	
	double phiStep = (oRadius - iRadius) / phiIteration;
	double thetaStep = (oRadius - iRadius) / thetaIteration;
	Vec3d coords;
	
	for (double i = 0, phi = 0; i <= this->phiIteration; i++, phi += phiStep) {
        for (double j = 0, theta = 0; j <= this->thetaIteration; j++, theta += thetaStep) {
            coords = Vec3d(
                this->(iRadius + oRadius* cos(2*PI*phi))* cos(2*PI*theta), // x
                this->(iRadius + oRadius* cos(2*PI*phi))* sin(2*PI*theta), // y
                this->0.5* sin(2*PI*phi)              // z
                /*normally: oRadius* sin(2*PI*phi), but we need the other notation for 
                			our rings*/
            );
            texcoords->push_back(Vec2(phi, theta));
            vertices->push_back(coords);
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
