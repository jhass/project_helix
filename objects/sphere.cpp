#include <osg/Geode>
#include <osg/Group>
#include <cmath>

#include "sphere.h"

using namespace std;

ph::Sphere::Sphere(const double radius, const int lsteps, const int wsteps) {
	this->radius = radius;
	this->lsteps = lsteps;
	this->wsteps = wsteps;
	this->addDrawable(this->compute());
}

Geometry* ph::Sphere::compute() {
	ref_ptr<Geometry> rect = new Geometry;
	ref_ptr<Vec3Array> vertices = new Vec3Array();
	ref_ptr<Vec3Array> normals = new Vec3Array();
	ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

	double sstep = this->radius / this->lsteps;
	double tstep = this->radius / this->wsteps;
	double s = 0.0, t;
	// current vertex coordinates
	double x = 0.0, y = 0.0, z = 0.0;
	
	Vec3d coords;

	// set vertices and normals
	for (double i = 0; i <= this->lsteps; i++) {
		t = 0.0;
		for (int j = 0; j <= this->wsteps; j++) {
			x = this->radius*cos(2*PI*s)*cos(PI*t-PI_2);
			y = this->radius*sin(2*PI*s)*cos(PI*t-PI_2);
			z = this->radius*sin(PI*t-PI_2);
			coords = Vec3d(x, y, z);
			vertices->push_back(coords);
			coords.normalize();
			normals->push_back(coords);
			t += tstep;
		}
		s += sstep;
	}


	for (int i = 0; i < this->lsteps; i++) {
		for (int j = 0; j <= this->wsteps; j++) {
			indices->push_back(i*(this->wsteps+1)+j);
			indices->push_back((i+1)*(this->wsteps+1)+j);
		}
		indices->push_back((i+1)*(this->wsteps+1)+this->wsteps);
		indices->push_back((i+1)*(this->wsteps+1));
	}

	rect->setVertexArray (vertices.get());
	rect->addPrimitiveSet(indices.get());
	rect->setNormalArray(normals.get());
	rect->setNormalBinding(Geometry::BIND_PER_VERTEX);

	return rect.release();
}
