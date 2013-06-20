#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <cmath>

#include "Rotator.h"

#include <osg/MatrixTransform>
#include <osg/Point>
#include <osg/PointSprite>
#include <osg/BlendFunc>
#include <osg/Texture2D>
#include <osgGA/StateSetManipulator>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RadialShooter>



ph::Rotator::Rotator(const double startx, const double endx, const int schritte) {
    
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
    double x,y,zstrich, idouble4, idouble3, idouble2, ystrich,z,yabl;
 double gesamtbereich=(fabs(startx)+fabs(endx));
 double teilex=gesamtbereich*schritte;
 int count=0;   
   

 for (double i = startx; i <=endx; i=i+0.1) { 
    	  // printf("%f\n",i);
    	    idouble4 = pow(i,4);
    	    idouble3 = pow(i,3);
            idouble2 = pow(i,2);
  
          
           y=(-0.125*idouble2)+.4;
           yabl=(-.25*i);

            for (int j = 0; j <= schritte;j++){ // einzelner Scheibenringe  von "hinten nach vorne" in 100 Teile zerlegt
                    
                    ystrich=(cos(2*PI/schritte*j)*y); 
                    z=(sin(2*PI/schritte*j)*y);
                    coords=Vec3d(i,ystrich, z);
                    
                    //z=-f(x)*f'(x)
                    
                    vertices->push_back(coords);
                   // printf("%f\n",x);
                    x=(double)count/(gesamtbereich*10);
                    double y_test=(double)j/schritte;
                    texcoords->push_back(Vec2d(x,y_test));
                    
                    coords = Vec3d(-(y)*yabl,ystrich,z);
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
   

    for (double i = 0; i < (gesamtbereich*10)-1; i++) {
    	    
        for (int j =0; j<=schritte ; j++){
            indices->push_back( (int)(i*( schritte+1)+j )) ;
            indices->push_back( (int)(( i +1)*(schritte+1)+j )) ;
        }
      
    }

    this->rotator->addPrimitiveSet(indices.get());
  
    
    
   
}

