#include <cmath>

#include "sphere.h"

using namespace std;

ph::Sphere::Sphere(const double radius, const int lsteps, const int wsteps) {
    this->radius = radius;
    this->lsteps = lsteps;
    this->wsteps = wsteps;
    this->sphere = new Geometry;
    this->addDrawable(this->sphere.get());
    this->compute();
}

ph::Sphere::~Sphere() {
    this->sphere.release();
}

void ph::Sphere::compute() {
    this->setVerticiesAndNormals();
    this->setIndicies();
}

void ph::Sphere::setVerticiesAndNormals() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();

    double sstep = this->radius/this->lsteps;
    double tstep = this->radius/this->wsteps;
    Vec3d coords; // current vertex coordinates

    for (double i = 0, s = 0; i <= this->lsteps; i++, s += sstep) {
        for (double j = 0, t = 0; j <= this->wsteps; j++, t += tstep) {
            coords = Vec3d(
                this->radius*cos(2*PI*s)*cos(PI*t-PI_2), // x
                this->radius*sin(2*PI*s)*cos(PI*t-PI_2), // y
                this->radius*sin(PI*t-PI_2)              // z
            );
            vertices->push_back(coords);
            coords.normalize();
            normals->push_back(coords);
        }
    }
    this->sphere->setVertexArray(vertices.get());
    this->sphere->setNormalArray(normals.get());
    this->sphere->setNormalBinding(Geometry::BIND_PER_VERTEX);
}


void ph::Sphere::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->lsteps; i++) {
        for (int j = 0; j <= this->wsteps; j++) {
            indices->push_back(i*(this->wsteps+1)+j);
            indices->push_back((i+1)*(this->wsteps+1)+j);
        }
        indices->push_back((i+1)*(this->wsteps+1)+this->wsteps);
        indices->push_back((i+1)*(this->wsteps+1));
    }
    
    this->sphere->addPrimitiveSet(indices.get());
}
