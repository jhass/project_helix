#include <cmath>

#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>

#include "Torus.h"

// Torus(Radius zum Ursprung, Radius des Torus, Iterationsschritte)
ph::Torus::Torus(const double iRadius, const double tRadius, const int iteration) {
    this->iRadius = iRadius; //radius from origin to the torus
    this->tRadius = tRadius; //radius of the torus
    this->iteration = iteration; //iterations for the torus-circle

    this->style = NORMAL;
    this->torus = new Geometry;

    this->addDrawable(this->torus.get());
    this->compute();
}

// setting Torusstyle = {FLAT, NORMAL}
void ph::Torus::setStyle(const Style style) {
    this->style = style;
    this->compute();
}

// setting texture on torus
void ph::Torus::setTexture(const int textureNumber, const string filename) {
    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}


void ph::Torus::compute() {
    this->setCoordinates();
    this->setIndicies();
}

// creating vertices / normals / texturecoordinates
void ph::Torus::setCoordinates() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    double phi, theta;
    
    for (double i = 0; i <= this->iteration; i++) {
        for (double j = 0; j <= this->iteration; j++) {
            phi = (double) j / iteration;
            theta = (double) i / iteration;
            vertices->push_back(calculateVertex(theta, phi));
            normals->push_back(calculateNormal(theta, phi));
            texcoords->push_back(Vec2(phi, theta));
        }
    }
    
    this->torus->setVertexArray(vertices.get());
    this->torus->setNormalArray(normals.get());
    this->torus->setNormalBinding(Geometry::BIND_PER_VERTEX);
    this->torus->setTexCoordArray(0, texcoords.get());
}

/* create vertex with x = (iRadius+ tRadius* cos(phi))* cos(theta)
                      y = (iRadius+ tRadius* cos(phi))* sin(theta)
                      z = tRadius* sin(phi) (Normal); tRadius = .5 (Flat) */
Vec3d ph::Torus::calculateVertex(const double theta, const double phi) {
    double z = 0;

    if (this->style == FLAT) {
        z = 0.1* sin(2*PI*phi);
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

// creating normals with correct spheric coordinates for torus
Vec3d ph::Torus::calculateNormal(const double theta, const double phi) {
    Vec3d coords = Vec3d(
        (this->tRadius* cos(2*PI*phi))* cos(2*PI*theta), // x
        (this->tRadius* cos(2*PI*phi))* sin(2*PI*theta), // y
         this->tRadius* sin(2*PI*phi)                    // z
    );

    coords.normalize();

    return coords;
}

// creating indices
void ph::Torus::setIndicies() {
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);

    for (int i = 0; i < this->iteration; i++) {
        for (int j = 0; j <= this->iteration; j++) {
            indices->push_back(i*(this->iteration+1)+j);
            indices->push_back((i+1)*(this->iteration+1)+j);
        }
        indices->push_back((i+1)*(this->iteration+1)+this->iteration);
        indices->push_back((i+1)*(this->iteration+1));
    }
    
    this->torus->addPrimitiveSet(indices.get());
}

// flat torus
ph::FlatTorus::FlatTorus(const double iRadius, const double tRadius, const int iteration) : Torus(iRadius, tRadius, iteration) {
    this->setStyle(FLAT);
}
