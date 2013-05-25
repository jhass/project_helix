#include <cmath>

#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>

#include "Sphere.h"

ph::Sphere::Sphere(const double radius, const int lsteps, const int wsteps) {
    this->radius = radius;
    this->lsteps = lsteps;
    this->wsteps = wsteps;
    this->sphere = new Geometry;
    this->addDrawable(this->sphere.get());
    this->compute();
}

void ph::Sphere::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}

void ph::Sphere::compute() {
    this->setVerticesAndNormals();
    this->setIndicies();
}

void ph::Sphere::setVerticesAndNormals() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    Vec3d coords;
    double theta, phi;

    // i == stack (v), j == slice (h)
    for (int i = 0; i <= this->wsteps; i++) {
        for (int j = 0; j < this->lsteps; j++) {
            theta = i * PI / this->wsteps;
            phi = j * 2 * PI / (this->lsteps-1);
            coords = Vec3d(
                radius * cos(phi) * sin(theta), 
                radius * sin(phi) * sin(theta), 
                radius * cos(theta)
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

    for (int i = 0; i < this->wsteps; i++) {
        for (int j = 0; j <= this->lsteps; j++) {     
            indices->push_back((i * this->lsteps + j % this->lsteps));
            indices->push_back(((i + 1) * this->lsteps) + (j % this->lsteps));
        }
    }
    
    this->sphere->addPrimitiveSet(indices.get());
}

void ph::Sphere::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    for (double j = this->lsteps; j >= 0; j--) {
        for (double i = 0; i < this->wsteps; i++) {
            texcoords->push_back(Vec2d(i/this->wsteps, j/this->lsteps));
        }
    }

    this->sphere->setTexCoordArray(textureNumber, texcoords.get());
}
