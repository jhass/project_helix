#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <cmath>

#include "Rotator.h"

/*TODO:

harte lsteps und wsteps ersetzen
Texturkoordinaten prüfen
normalen basteln
*/


ph::Rotator::Rotator(const int startx, const int endx, const int schritte) {
    
    this->startx = startx;
    this->endx = endx;
    this->schritte = schritte;
    this->rotator = new Geometry;
    this->addDrawable(this->rotator.get());
    this->compute();
}

ph::Rotator::~Rotator() {
    this->rotator.release();
}

void ph::Rotator::setTexture(const int textureNumber, const string filename) {
   // this->setTextureCoordinates(textureNumber);

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
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
    ref_ptr<Vec2Array> texcoords = new Vec2Array();
    Vec3d coords;
    double x,y,zstrich, idouble4, idouble3, idouble2, ystrich,z;
 int gesamtbereich=(int)(fabs(startx)+fabs(endx));
 int count=0;   
    for (int i = (int)startx; i <=(int)endx; i++) { // X-Achsenpunkte *50 -> Schritte x
    	   
    	    idouble4 = pow(i,4);
    	    idouble3 = pow(i,3);
            idouble2 = pow(i,2);
  

           y=(-0.0003*idouble2)+50;

            for (int j = 0; j <= schritte;j++){ // einzelner Scheibenringe  von "hinten nach vorne" in 100 Teile zerlegt
                    
                    ystrich=(cos(2*PI/schritte*j)*y); 
                    z=(sin(2*PI/schritte*j)*y);
                    coords=Vec3d(i,ystrich, z);
           
                    vertices->push_back(coords);
                    x=(double)count/gesamtbereich;
                    double y_test=(double)j/schritte;
                    texcoords->push_back(Vec2d(x,y_test));
                   
                    coords.normalize();
                  
                    normals->push_back(coords); //Skript & Benni hilft bestimmt -- Vektor verschieben zum Schnittkreismittelpunkt
                            
            }                       
     count++;
    }

    this->rotator->setVertexArray(vertices.get());
    this->rotator->setNormalArray(normals.get());
    this->rotator->setNormalBinding(Geometry::BIND_PER_VERTEX);
    this->rotator->setTexCoordArray(0, texcoords.get());
   
}

void ph::Rotator::setIndicies() { 

    int gesamtbereich=(int)(fabs(startx)+fabs(endx));
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);
   

    for (int i = 0; i < gesamtbereich ; i++) {
    	    
        for (int j =0; j<=schritte ; j++){
            indices->push_back( (int)(i*( schritte+1)+j )) ;
            indices->push_back( (int)(( i +1)*(schritte+1)+j )) ;
        }
      
    }

    this->rotator->addPrimitiveSet(indices.get());
  
    
    
   
}

/*void ph::Rotator::setTextureCoordinates(int textureNumber) {
    ref_ptr<Vec2Array> texcoords = new Vec2Array;
 int gesamtbereich=(int)(fabs(startx)+fabs(endx));
  double  y,ystrich,z,idouble2;  
      
  for (int i = 0; i <=gesamtbereich; i++) { // X-Achsenpunkte  Schritte x
        idouble2 = pow(i,2);
  	  y=(-0.0003*idouble2)+50;
  	  for (int j = 0; j <= schritte;j++){ // einzelner Scheibenringe  von "hinten nach vorne" in 100 Teile zerlegt
                    
             
                    z=(sin(2*PI/schritte*j)*y);
                    ystrich=(double)i/gesamtbereich;
              
                    texcoords->push_back(Vec2d(z,i));
                  
            }                       
 }
 

    this->rotator->setTexCoordArray(textureNumber, texcoords.get());
}*/

