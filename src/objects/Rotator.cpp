#include <cmath>

#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include "Rotator.h"


ph::Rotator::Rotator(const double startx, const double endx, const int schritte) {
    
    this->startx = startx;
    this->endx = endx;
    this->schritte = schritte;
    this->rotator = new Geometry;
    this->addDrawable(this->rotator.get());
    this->compute();
}

void ph::Rotator::setTexture(const int textureNumber, const string filename) {

    ref_ptr<Texture2D> texture = new Texture2D;
    ref_ptr<Image> image = osgDB::readImageFile(filename);
    texture->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
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
    double x, y, idouble2, ystrich, z, yabl, gesamtbereich=(fabs(startx)+fabs(endx));
    int count=0;   
   

 for (double i = startx; i <=endx; i=i+0.1) { // Durchlaufen der X-Achse vom -x nach x in 0.1er Schritten
            
 	   idouble2 = pow(i,2);
           y=(-0.125*idouble2)+.4;  // f(x)=-0.125x^2+0.4
           yabl=(-.25*i);

            for (int j = 0; j <= schritte;j++){ // einzelner Scheibenringe  von "hinten nach vorne" in 'schritte' Teile zerlegt
                    
                    ystrich=(cos(2*PI/schritte*j)*y); 
                    z=(sin(2*PI/schritte*j)*y);
                    coords=Vec3d(i,ystrich, z);
                    vertices->push_back(coords);
                    
                    x=(double)count/(gesamtbereich*10);
                    double y_test=(double)j/schritte;
                    
                    texcoords->push_back(Vec2d(x,y_test));
                    
                    coords = Vec3d(-(y)*yabl,ystrich,z);     //Normalenberechnung des Z-Wertes z=-f(x)*f'(x)
                    coords.normalize();
                    normals->push_back(coords); 
                            
            }                       
     count++;
    }

    this->rotator->setVertexArray(vertices.get());
    this->rotator->setNormalArray(normals.get());
    this->rotator->setNormalBinding(Geometry::BIND_PER_VERTEX);
    this->rotator->setTexCoordArray(0, texcoords.get());
   
}

void ph::Rotator::setIndicies() { 

    double gesamtbereich=(fabs(startx)+fabs(endx));
    ref_ptr<DrawElementsUInt> indices = new DrawElementsUInt(GL_TRIANGLE_STRIP);
   

    for (double i = 0; i < (gesamtbereich*10)-1; i++) {  //*10 da die Vertices in 0.1er Schritten gesetzt wurden
    	    
        for (int j =0; j<=schritte ; j++){
            indices->push_back( (int)(i*( schritte+1)+j )) ;
            indices->push_back( (int)(( i +1)*(schritte+1)+j )) ;
        }
      
    }

    this->rotator->addPrimitiveSet(indices.get());
  
    
    
   
}

