#include <cmath>
#include <cstdlib>

#include <osg/Texture2D>
#include <osg/Material>
#include <osgDB/ReadFile>

#include "Asteroid.h"

using namespace std;

/* Asteriod (radius, Iterationsschritte horizontal, Iterationsschritte vertikal
             Deformation in x, y, z) */
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

/* creating vertices/ normals / texturecoordinates analog to sphere
   with random changes in radius with value +-10% of the radius;
   in addition there is a deformation factor for x, y, z stretching or
   compressing the object in the corresponding spatial direction */
void ph::Asteroid::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    Vec3d coords; // current vertex coordinates
    double theta, phi;

    for (int i = 0; i <= this->wsteps; i++) {
        for (int j = 0; j < this->lsteps; j++) {
            theta = i * PI / this->wsteps;
            phi = j * 2 * PI / (this->lsteps-1);
            int random = rand() % 20;
            // random change of radius
			double nradius = this->radius + (random -10) * this->radius/100;
			// xd, yd, zd = deformation factors
            coords = Vec3d(
                xd*nradius * cos(phi) * sin(theta), 
                yd*nradius * sin(phi) * sin(theta), 
                zd*nradius * cos(theta)
            );
            vertices->push_back(coords);
            coords.normalize();
            normals->push_back(coords);
        }
    }
    this->asteroid->setVertexArray(vertices.get());
    this->asteroid->setNormalArray(normals.get());
    this->asteroid->setNormalBinding(Geometry::BIND_PER_VERTEX);
}

// creating indices analog to sphere
void ph::Asteroid::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->wsteps; i++) {
        for (int j = 0; j <= this->lsteps; j++) {     
            indices->push_back((i * this->lsteps + j % this->lsteps));
            indices->push_back(((i + 1) * this->lsteps) + (j % this->lsteps));
        }
    }
    
    this->asteroid->addPrimitiveSet(indices.get());
}

// creating texture coordinates
void ph::Asteroid::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    for (double j = this->lsteps; j >= 0; j--) {
        for (double i = 0; i < this->wsteps; i++) {
            texcoords->push_back(Vec2d(i/this->wsteps, j/this->lsteps));
        }
    }

    this->asteroid->setTexCoordArray(textureNumber, texcoords.get());
}

//setting texture on asteroid
void ph::Asteroid::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    
    // Creating Material for the Cuboid
    ref_ptr<Material> material = new Material;
    // material emits giving light (R,G,B,x)
    material->setEmission(Material::FRONT_AND_BACK, Vec4(0.5,0.5,0.5,1));
    
    // material parameters; perhaps we need some of them later
    material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.5,0.5,0.5,1.0));
    material->setAmbient(Material::FRONT_AND_BACK, Vec4(0.5,0.5,0.5,1.0));
    material->setSpecular(Material::FRONT_AND_BACK, Vec4(1,1,1,1));
    material->setShininess(Material::FRONT_AND_BACK, 30);
    
    //giving the material to the sphere
    this->getOrCreateStateSet()->setAttributeAndModes(material.get(),StateAttribute::ON);
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}
