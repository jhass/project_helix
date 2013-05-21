#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "asteroid.h"

using namespace std;

ph::Asteroid::Asteroid(const double radius, const int lsteps, const int wsteps,
                       const int xi, const int yi, const int zi) {
    this->radius = radius;
    this->lsteps = lsteps;
    this->wsteps = wsteps;
    this->xd = xi;
    this->yd = yi;
    this->zd = zi;
    this->asteroid = new Geometry;
    this->addDrawable(this->asteroid.get());
    this->compute();
}

ph::Asteroid::~Asteroid() {
    this->asteroid.release();
}

void ph::Asteroid::compute() {
    this->setCoordinates();
    this->setIndicies();
}

void ph::Asteroid::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    double sstep = this->radius/this->lsteps;
    double tstep = this->radius/this->wsteps;
    Vec3d coords; // current vertex coordinates
    srand( time(NULL) );
    double x = 0, y = 0, z = 0;

    for (double i = 0, s = 0; i <= this->lsteps; i++, s += sstep) {
        for (double j = 0, t = 0; j <= this->wsteps; j++, t += tstep) {
        	int random = rand() % 20;
			double nradius = this->radius + (random -10) * this->radius/100;
        	x = this->xd*nradius*cos(2*PI*s)*cos(PI*t-PI_2);
        	y = this->yd*nradius*sin(2*PI*s)*cos(PI*t-PI_2);
        	z = this->zd*nradius*sin(PI*t-PI_2);
            coords = Vec3d(x,y,z);            
            vertices->push_back(coords);
            coords.normalize();
            normals->push_back(coords);
        } 
    }
    this->asteroid->setVertexArray(vertices.get());
    this->asteroid->setNormalArray(normals.get());
    this->asteroid->setNormalBinding(Geometry::BIND_PER_VERTEX);
}


void ph::Asteroid::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->lsteps; i++) {
        for (int j = 0; j <= this->wsteps; j++) {
            indices->push_back(i*(this->wsteps+1)+j);
            indices->push_back((i+1)*(this->wsteps+1)+j);
        }
        indices->push_back((i+1)*(this->wsteps+1)+this->wsteps);
        indices->push_back((i+1)*(this->wsteps+1));
    }
    
    this->asteroid->addPrimitiveSet(indices.get());
}
