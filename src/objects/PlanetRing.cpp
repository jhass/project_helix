#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Material>

#include "PlanetRing.h"

ph::PlanetRing::PlanetRing(const double iRadius, const double tRadius, const int iteration) :
    Torus(iRadius, tRadius, iteration) {
    this->setStyle(ph::Torus::FLAT);
    this->setRingTexture();
}

//creates 1d texture based on osgtexture1d code example
void ph::PlanetRing::setRingTexture() {

    Image* image = new Image;
    int pixels = 1000;
    
    // image anlegen mit pixels x 1 x 1 und RGBA dargestellt durch Vec4
    image->allocateImage(pixels, 1, 1, GL_RGBA,GL_FLOAT);
    image->setInternalTextureFormat(GL_RGBA);
    
    // creating colors
    vector<Vec4> colorBands;
    colorBands.push_back(Vec4(0.0, 0.0, 0.0, 1.0));
    colorBands.push_back(Vec4(0.1, 0.1, 0.1, 1.0));
    colorBands.push_back(Vec4(0.2, 0.2, 0.2, 1.0));
    colorBands.push_back(Vec4(0.3, 0.3, 0.3, 1.0));
    colorBands.push_back(Vec4(1.0, 1.0, 1.0, 1.0));
    
    int pos = 0, count = 0;
    
    /* creating image data (% Pixel; symmetrical)
       10 % dark grey; 3% black; 5% light grey;
       2% black; 10% light grey; 2% black;
       5% light grey; 3% black; 5% light grey
       5% dark grey*/
    Vec4* dataPoints = (Vec4*)image->data();
    for (int k=1; k <=2; k++) {
        for(int i=0; i<pixels/10; i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
        }
        
        pos += count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/10); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+2*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[2];
            *dataPoints++ = color;
            count = i;
        }

        pos += count;
        for(int i=pos; i<(pos+3*pixels/100); i++) {
            Vec4 color = colorBands[0];
            *dataPoints++ = color;
            count = i;
        }  
        
        pos += count;
        for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[3];
            *dataPoints++ = color;
            count = i;
        }
        
       pos += count;
       for(int i=pos; i<(pos+pixels/20); i++) {
            Vec4 color = colorBands[1];
            *dataPoints++ = color;
            count = i;
        }
        pos += count;
    }
    
    Texture1D* texture = new Texture1D;
    texture->setWrap(Texture1D::WRAP_T, Texture::MIRROR);
    texture->setFilter(Texture1D::MIN_FILTER, Texture::NEAREST);
    texture->setImage(image);
    
    Material* material = new Material;
    StateSet* stateSet = new StateSet;
    
    stateSet->setTextureAttribute(0, texture, StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0, GL_TEXTURE_1D, StateAttribute::ON|StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0, GL_TEXTURE_2D, StateAttribute::OFF|StateAttribute::OVERRIDE);
    stateSet->setTextureMode(0, GL_TEXTURE_3D, StateAttribute::OFF|StateAttribute::OVERRIDE);
    
    stateSet->setAttribute(material, StateAttribute::OVERRIDE);
    material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.1,0.1,0.1,1.0));
    material->setAmbient(Material::FRONT_AND_BACK, Vec4(1,1,1,1.0));
    material->setSpecular(Material::FRONT_AND_BACK, Vec4(1,1,1,1));
    material->setShininess(Material::FRONT_AND_BACK, 30);

    this->setStateSet(stateSet);
}
