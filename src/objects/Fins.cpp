#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <cmath>

#include "Fins.h"


//Position sinnlos, da viewer das ignoriert
//normalen passen noch nicht

ph::Fins::Fins(const int position, const int factor) {
    
    this->position = position;
    this->factor = factor;
    this->fins = new Geometry;
    
    this->addDrawable(this->fins.get());                           
    this->compute();
}

ph::Fins::~Fins() {
    this->fins.release();
}

void ph::Fins::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
   // texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}

void ph::Fins::compute() {
	this->setFins(this->factor);

}

void ph::Fins::setFins(int factor) {
	
    ref_ptr<Vec3Array> vertices = new Vec3Array();
     ref_ptr<Vec3Array> normals = new Vec3Array();
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);
    Vec3d coords;
     ref_ptr<Vec2Array> texcoords = new Vec2Array;
        
    vertices->push_back(Vec3(0,0,0)); //Spitze (links)
    normals->push_back(Vec3(0,0,1)); //Spitze (links)
    
    
    vertices->push_back(Vec3(1*factor,0,0)); //Heck
    normals->push_back(Vec3(1*factor,0,1)); //Heck
   
    
    vertices->push_back(Vec3(1*factor,2*factor,0)); //Oben
    normals->push_back(Vec3(1*factor,2*factor,1)); //Oben

    
 //   vertices->push_back(Vec3(1*factor,0,2*factor)); // Vorne
 //   normals->push_back(Vec3(1*factor,1,2*factor)); // Vorne

    
 //   vertices->push_back(Vec3(1*factor,0,-2*factor)); // Hinten
 //   normals->push_back(Vec3(1*factor,1,-2*factor)); // Hinten

     
 //   vertices->push_back(Vec3(1*factor,-2*factor,0)); //unten
 //   normals->push_back(Vec3(1*factor,-2*factor,1)); //unten
 
    
    indices->push_back(0); indices->push_back(1); indices->push_back(2);
 //   indices->push_back(0); indices->push_back(1); indices->push_back(3);
 //   indices->push_back(4); indices->push_back(1); indices->push_back(0);
 //   indices->push_back(5); indices->push_back(1); indices->push_back(0);
    
    this->fins->setVertexArray(vertices.get());
    this->fins->addPrimitiveSet(indices.get());
    this->fins->setNormalBinding(Geometry::BIND_OVERALL);  
    //normalen noch spiegeln

}

void ph::Fins::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    texcoords->push_back(Vec2(0.0,0.0));
    texcoords->push_back(Vec2(1.0,0.0));
    texcoords->push_back(Vec2(1.0,1.0));
    texcoords->push_back(Vec2(1.0,1.0));
    texcoords->push_back(Vec2(1.0,1.0));
    texcoords->push_back(Vec2(1.0,1.0));
    
    this->fins->setTexCoordArray(textureNumber, texcoords.get());
}
