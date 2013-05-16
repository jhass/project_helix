#include "sphere.h"

Geometry* createSphere(const double radius, const int lsteps, const int wsteps) {

	ref_ptr<Geometry> rect = new Geometry;
	ref_ptr<Vec3Array> vertices = new Vec3Array();
	ref_ptr<Vec3Array> normals = new Vec3Array();
	ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

	double sstep = radius / lsteps;
	double tstep = radius / wsteps;
	double s = 0.0,t = 0.0;
	// current vertex coordinates
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	
	Vec3d coords;

	// set vertices and normals
	for (int i=0; i<= lsteps; i++){
		t = 0.0;
		for (int j=0; j<=wsteps; j++){
			x = radius* cos(2*PI*s)* cos(PI*t - PI_2);
			y = radius* sin(2*PI*s)* cos(PI*t - PI_2);
			z = radius* sin(PI*t - PI_2);
			coords = Vec3d(x,y,z);
			vertices->push_back(coords);
			coords.normalize();
			normals->push_back(coords);
			t += tstep;
		}
		s += sstep;
	}


	for (int i=0; i <lsteps; i++){

		for (int j=0; j<=wsteps; j++){
			indices->push_back( i*(wsteps+1)+j );
			indices->push_back( (i+1)*(wsteps+1)+j );
		}
		indices->push_back( (i+1)*(wsteps+1)+wsteps );
		indices->push_back( (i+1)*(wsteps+1) );
	}

	rect->setVertexArray (vertices.get());
	rect->addPrimitiveSet(indices.get());
	rect->setNormalArray(normals.get());
	rect->setNormalBinding(Geometry::BIND_PER_VERTEX);

	return rect.release();
}
