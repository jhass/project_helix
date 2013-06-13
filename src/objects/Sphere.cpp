#include <cmath>

#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>

#include "Sphere.h"

// Sphere(radius, Iterationsschritte)
ph::Sphere::Sphere(const double radius, const int steps) {
    this->radius = radius;
    this->steps = steps;
    this->sphere = new Geometry;
    this->addDrawable(this->sphere.get());
    this->compute();
}

void ph::Sphere::compute() {
    this->setVerticesAndNormals();
    this->setIndicies();
}

// creating vertices / normals
void ph::Sphere::setVerticesAndNormals() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    Vec3d coords;
    double theta, phi;

    /* creating coordinates in spheric coordinates with
        x = r* cos(phi)* sin(theta); y= r* sin(phi)* sin(theta)
        z = r* cos(theta) */
    for (int i = 0; i <= this->steps; i++) {
        for (int j = 0; j < this->steps; j++) {
            theta = i * PI / this->steps;
            phi = j * 2 * PI / (this->steps-1);
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

// creating indices radial from bottom to top
void ph::Sphere::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->steps; i++) {
        for (int j = 0; j <= this->steps; j++) {     
            indices->push_back((i * this->steps + j % this->steps));
            indices->push_back(((i + 1) * this->steps) + (j % this->steps));
        }
    }
    
    this->sphere->addPrimitiveSet(indices.get());
}

// creating texture coordinates
void ph::Sphere::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    for (double j = this->steps; j >= 0; j--) {
        for (double i = 0; i < this->steps; i++) {
            texcoords->push_back(Vec2d(i/this->steps, j/this->steps));
        }
    }

    this->sphere->setTexCoordArray(textureNumber, texcoords.get());
}

// setting texture on sphere
void ph::Sphere::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}
