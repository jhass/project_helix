#include <cmath>

#include <osg/Texture2D>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osg/CullFace>

#include "Rectangle.h"

// Rectangle (heigth, witdth)
ph::Rectangle::Rectangle(const int height, const int width) {
    this->height = height;
    this->width = width;
    this->rectangle = new Geometry;
    this->addDrawable(rectangle);
    
    compute();
}

// creating vertices/ normals / indices; simple rectangle build from two triangles
void ph::Rectangle::compute() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);
    
    vertices->push_back(Vec3((-1/2.0)*height, 0.0, (-1/2.0)*width));
    vertices->push_back(Vec3((1/2.0)*height, 0.0, (-1/2.0)*width));
    vertices->push_back(Vec3((-1/2.0)*height, 0.0, (1/2.0)*width));
    vertices->push_back(Vec3((1/2.0)*height, 0.0, (1/2.0)*width));
    
    indices->push_back(0); indices->push_back(1); indices->push_back(2);
    indices->push_back(1); indices->push_back(2); indices->push_back(3);
     
    this->rectangle->setVertexArray(vertices.get());
    this->rectangle->addPrimitiveSet(indices.get());
}

// creating texture coordinates
void ph::Rectangle::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    texcoords->push_back(Vec2(0.0,0.0));
    texcoords->push_back(Vec2(1.0,0.0));
    texcoords->push_back(Vec2(0.0,1.0));
    texcoords->push_back(Vec2(1.0,1.0));
    
    this->rectangle->setTexCoordArray(textureNumber, texcoords.get());
}

// setting texture on rectangle
void ph::Rectangle::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
    
    // enabling culling for rectangles / skybox
    ref_ptr<CullFace> cull = new CullFace;
    cull->setMode(CullFace::BACK);
    this->getOrCreateStateSet()->setAttributeAndModes(cull.get());
}
