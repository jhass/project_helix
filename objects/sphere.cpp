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
    this->setCoordinates();
    this->setIndicies();
}

void ph::Sphere::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

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
            texcoords->push_back(Vec2(s, t));
            vertices->push_back(coords);
            coords.normalize();
            normals->push_back(coords);
        }
    }
    this->sphere->setVertexArray(vertices.get());
    this->sphere->setNormalArray(normals.get());
    this->sphere->setTexCoordArray(0, texcoords.get());
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


StackedSphere::StackedSphere(const double radius, const int wsteps, const int lsteps) {
    ref_ptr<Vec3Array> verticies = new Vec3Array;
    ref_ptr<DrawElementsUInt> indicies = new DrawElementsUInt(GL_TRIANGLE_STRIP);
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;
    Vec3d coords;
    double theta, phi;

    // i == stack (v), j == slice (h)
    for (int i = 0; i <= wsteps; i++) {
        for (int j = 0; j < lsteps; j++) {
            theta = i * PI / wsteps;
            phi = j * 2 * PI / lsteps;
            coords = Vec3d(
                radius * cos(phi) * sin(theta), 
                radius * sin(phi) * sin(theta), 
                radius * cos(theta)
            );
            texcoords->push_back(Vec2d(i/(double) wsteps, j/(double) lsteps)); // noch blödsinn
            verticies->push_back(coords);
            coords.normalize();
            normals->push_back(coords);
        }
    }
    
    for (int i = 0; i < wsteps; i++) {
        for (int j = 0; j <= lsteps; j++) {
            indicies->push_back((i * lsteps) + (j % lsteps));
            indicies->push_back(((i + 1) * lsteps) + (j % lsteps));
        }
    }

    ref_ptr<Geometry> sphere = new Geometry;
    sphere->setVertexArray(verticies.get());
    sphere->setNormalArray(normals.get());
    sphere->setNormalBinding(Geometry::BIND_PER_VERTEX);
    sphere->addPrimitiveSet(indicies);
    sphere->setTexCoordArray(0, texcoords);
    this->addDrawable(sphere.get());
}
