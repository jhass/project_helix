#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <cmath>

#include "Rotator.h"

/*TODO:
indices prüfen
harte lsteps und wsteps ersetzen
Texturkoordinaten prüfen
normalen basteln
*/


ph::Rotator::Rotator(const double startx, const double endx) {
    
    this->startx = startx;
    this->endx = endx;
    this->rotator = new Geometry;
    this->addDrawable(this->rotator.get());
    this->compute();
}

ph::Rotator::~Rotator() {
    this->rotator.release();
}

void ph::Rotator::setTexture(const int textureNumber, const string filename) {
    this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP);
    texture->setImage(image.get());
    this->getOrCreateStateSet()->setTextureAttributeAndModes(textureNumber, texture.get());
}

void ph::Rotator::compute() {
    this->setVerticesAndNormals();
    this->setIndicies();
}

void ph::Rotator::setVerticesAndNormals() {
    ref_ptr<Vec3Array> vertices = new Vec3Array();
    ref_ptr<Vec3Array> normals = new Vec3Array();
    Vec3d coords;
    double x,y,z,ystrich,zstrich, idouble4, idouble2;
    

    
    
    for (int i = startx*50; i <endx*50; i++) { // X-Achsenpunkte *50 -> Schritte x
            idouble4 = pow(i/50,4);
            idouble2 = pow(i/50,2);
            y=-0,5*idouble4+8*idouble2+0.5;
            
            for (int j = 0; j < 100;j++){ // einzelner Scheibenringe  von "hinten nach vorne" in 100 Teile zerlegt
                    
                    ystrich=cos(360/100*j)/y;
                    z=sin(360/100*j)/y;
                    coords=Vec3d(i/100,ystrich, z);
                    vertices->push_back(coords);
                    coords.normalize();
                    normals->push_back(coords); //Skript & Benni hilft bestimmt -- Vektor verschieben zum Schnittkreismittelpunkt
                            
            }                       
    }
             //rotationskörper

    this->rotator->setVertexArray(vertices.get());
    this->rotator->setNormalArray(normals.get());
    this->rotator->setNormalBinding(Geometry::BIND_PER_VERTEX);
}

void ph::Rotator::setIndicies() {
    
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);
    for (int i = 0; i < fabs(startx*50)+fabs(endx*50) ; i++) {
        for(int j =0; j<=100 ; j++){
            indices->push_back( i*( 100+1)+j ) ;
            indices->push_back( ( i +1)*(100+1)+j ) ;
        }
        indices->push_back( ( i +1)*(100+1)+fabs(startx*50)+fabs(endx*50)  ) ;
        indices->push_back( ( i +1)*(100+1) ) ;
    }
    
    this->rotator->addPrimitiveSet(indices.get());
  
    
    
   
}

void ph::Rotator::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;

    for (double j = 100; j >= 0; j--) {
        for (double i = 0; i < fabs(startx*50)+fabs(endx*50); i++) {
            texcoords->push_back(Vec2d(i/100, j/fabs(startx*50)+fabs(endx*50)));
        }
    }

    this->rotator->setTexCoordArray(textureNumber, texcoords.get());
}

