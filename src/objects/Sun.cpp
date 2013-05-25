#include "Sun.h"

ph::Sun::Sun(const double radius, const int lsteps, const int wsteps, const int lightNumber) {
    this->sphere = new Sphere(radius, lsteps, wsteps);
    this->addChild(this->sphere);
    this->createLight(lightNumber);
}

void ph::Sun::createLight(int lightNumber) {
    this->light = new Light;
    this->light->setLightNum(lightNumber);
    this->light->setPosition(Vec4(0.0,0.0,0.0,1.0));
    this->light->setDiffuse(Vec4(1.0,1.0,1.0,1.0));
    this->light->setSpecular(Vec4(1.0,1.0,1.0,1.0));
    //this->light->setAmbient(Vec4(0.0,0.0,0.0,0.0));
    
    this->source = new LightSource;
    this->source->setLight(light);
    this->source->setLocalStateSetModes(StateAttribute::ON);
    this->source->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::ON);
    this->addChild(this->source);
    
    this->material = new Material;
    this->material->setEmission(Material::FRONT_AND_BACK, Vec4(0.9,0.6,0.0,1.0));
    
    //this->material->setDiffuse(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setAmbient(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setSpecular(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setShininess(Material::FRONT_AND_BACK, 1);
    
    this->getOrCreateStateSet()->setAttributeAndModes(this->material.get(),StateAttribute::ON);
}
