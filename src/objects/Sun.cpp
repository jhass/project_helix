#include "Sun.h"

ph::Sun::Sun(const double radius, const int lsteps, const int wsteps, const int lightNumber) {
    this->sphere = new Sphere(radius, lsteps, wsteps);
    this->addChild(this->sphere);
    this->createLight(lightNumber);
}

void ph::Sun::createLight(int lightNumber) {

	// Creating a white light source in the interior of the sphere
	// creating a new light
    this->light = new Light;
    // giving the light an OpenGL-Lightnumber [0,7]
    this->light->setLightNum(lightNumber);
    // giving the light a position
    // setPosition(x,y,z,sourcetype); sourcetype = {0.0 (global), 1.0 (local)}
    this->light->setPosition(Vec4(0.0,0.0,0.0,1.0));
    // setting parameter for diffuse light
    this->light->setDiffuse(Vec4(1.0,1.0,1.0,1.0));
    // setting parameter for specular light
    this->light->setSpecular(Vec4(1.0,1.0,1.0,1.0));
    
    // atm we dont want ambient light
    //this->light->setAmbient(Vec4(0.0,0.0,0.0,0.0));
    
    // creating a new light source
    this->source = new LightSource;
    // giving the source a light
    this->source->setLight(light);
    // switch the light on
    this->source->setLocalStateSetModes(StateAttribute::ON);
    this->source->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::ON);
    this->addChild(this->source);
    
    // Creating Material for the Sun
    this->material = new Material;
    // material emits giving light (R,G,B,x)
    this->material->setEmission(Material::FRONT_AND_BACK, Vec4(0.9,0.6,0.0,1.0));
    
    // material parameters; perhaps we need some of them later
    //this->material->setDiffuse(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setAmbient(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setSpecular(Material::FRONT_AND_BACK, Vec4(1.0,0.0,0.0,1.0));
    //this->material->setShininess(Material::FRONT_AND_BACK, 1);
    
    //giving the material to the sphere
    this->getOrCreateStateSet()->setAttributeAndModes(this->material.get(),StateAttribute::ON);
}