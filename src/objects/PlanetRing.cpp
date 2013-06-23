#include <osg/Texture1D>
#include <osg/Material>
#include <osg/Depth>
#include <osg/BlendFunc>

#include "PlanetRing.h"

// creates a planet ring from a flat torus with self-created 1D ringtexture
ph::PlanetRing::PlanetRing(const double iRadius, const double tRadius, const int iteration) :
    Torus(iRadius, tRadius, iteration) {
    this->setStyle(ph::Torus::FLAT);
    this->enableBlending();
    this->setRingTexture();
}

//creates 1d texture based on osgtexture1d code example
void ph::PlanetRing::setRingTexture() {

    Image* image = new Image;
    int pixels = 1024;

    /* setting up image with pixels x 1 x 1, colormodel RGBA 
       and colors defined in Vec4*/
    image->allocateImage(pixels, 1, 1, GL_RGBA,GL_FLOAT);
    image->setInternalTextureFormat(GL_RGBA);

    // creating colors (red,green,blue,alpha)
    vector<Vec4> colorBands;
    colorBands.push_back(Vec4(0.0, 0.0, 0.0, 0.0)); // transparent
    colorBands.push_back(Vec4(0.1, 0.1, 0.1, 1.0)); // dark-grey
    colorBands.push_back(Vec4(0.2, 0.2, 0.2, 1.0)); // grey
    colorBands.push_back(Vec4(0.3, 0.3, 0.3, 1.0)); // light-grey
    colorBands.push_back(Vec4(1.0, 1.0, 1.0, 1.0)); // white

    int pos = 0, count = 0;

    // creating image data (% Pixelnumber; symmetrical)
    Vec4* dataPoints = (Vec4*)image->data();

    /* 10 % dark grey; 3% black; 5% light grey;
       2% black; 10% light grey; 2% black;
       5% grey; 3% black; 5% light grey
       5% dark grey*/
    // first half    
    // dark-grey
    for(int i=0; i<pixels/10; i++) {
        Vec4 color = colorBands[1];
        *dataPoints++ = color;
    }

    pos += count;
    // black
    for(int i=pos; i<(pos+3*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // black
    for(int i=pos; i<(pos+2*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/10); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // black
    for(int i=pos; i<(pos+2*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[2];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // black
    for(int i=pos; i<(pos+3*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }  

    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // dark-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[1];
        *dataPoints++ = color;
        count = i;
    }

    /* 5% dark grey; 5% light grey; 3% black;
       5% grey; 2% black; 10% light grey;
       2% black; 5% light grey; 3% black
       10% dark grey*/
    // second half
    pos += count;
    // dark-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[1];
        *dataPoints++ = color;
        count = i;
    }

    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // black
    for(int i=pos; i<(pos+3*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[2];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // black
    for(int i=pos; i<(pos+2*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/10); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // black
    for(int i=pos; i<(pos+2*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // light-grey
    for(int i=pos; i<(pos+pixels/20); i++) {
        Vec4 color = colorBands[3];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // black
    for(int i=pos; i<(pos+3*pixels/100); i++) {
        Vec4 color = colorBands[0];
        *dataPoints++ = color;
        count = i;
    }
    
    pos += count;
    // dark-grey
    for(int i=0; i<pixels/10; i++) {
        Vec4 color = colorBands[1];
        *dataPoints++ = color;
    }
    
    Texture1D* texture = new Texture1D;
    
    // setting up 1Dtexture to wrap it on the ring
    texture->setWrap(Texture1D::WRAP_T, Texture::MIRROR);
    texture->setFilter(Texture1D::MIN_FILTER, Texture::NEAREST);
    texture->setImage(image);
    
    Material* material = new Material;
    ref_ptr<StateSet> state_set = this->getOrCreateStateSet();
    
    // setting stateset
    state_set->setTextureAttribute(0, texture, StateAttribute::OVERRIDE);
    state_set->setTextureMode(0, GL_TEXTURE_1D, StateAttribute::ON|StateAttribute::OVERRIDE);
    state_set->setTextureMode(0, GL_TEXTURE_2D, StateAttribute::OFF|StateAttribute::OVERRIDE);
    state_set->setTextureMode(0, GL_TEXTURE_3D, StateAttribute::OFF|StateAttribute::OVERRIDE);
    
    state_set->setAttribute(material, StateAttribute::OVERRIDE);
    
    // setting material attributes for reflection
    material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.1,0.1,0.1,1.0));
    material->setAmbient(Material::FRONT_AND_BACK, Vec4(1,1,1,1.0));
    material->setSpecular(Material::FRONT_AND_BACK, Vec4(1,1,1,1));
    material->setShininess(Material::FRONT_AND_BACK, 30);

    this->setStateSet(state_set.get());
}


void ph::PlanetRing::enableBlending() {
    ref_ptr<StateSet> state_set = this->getOrCreateStateSet();
    
    // enables blending for transparent parts of the ring
    ref_ptr<BlendFunc> blendFunc = new BlendFunc;
    blendFunc->setFunction( BlendFunc::SRC_ALPHA, BlendFunc::ZERO);
    state_set->setAttributeAndModes(blendFunc);
   
    state_set->setRenderingHint(StateSet::TRANSPARENT_BIN);
   
    this->setStateSet(state_set.get());
}
