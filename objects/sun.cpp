#include "sphere.h"
#include "sun.h"

ph::Sun::Sun(const double radius, const int lsteps, const int wsteps, const int lightNumber) :
										ph::Sphere::Sphere(radius, lsteps, wsteps) {
	this->createLight(lightNumber);
}

ph::Sun::~Sun() {
	this->light.release();
	this->source.release();
}

void ph::Sun::createLight(int lightNumber) {
	this->light = new Light;
	this->light->setLightNum(lightNumber);
	this->light->setPosition(Vec4(0.0,0.0,0.0,1.0));
	this->light->setDiffuse(Vec4(1.0,1.0,1.0,1.0));
	this->light->setSpecular(Vec4(1.0,1.0,1.0,1.0));
	
	this->source = new LightSource;
	this->source->setLight(light);
}

void ph::Sun::setLight(ref_ptr<Group> &node) {
	node->addChild(this->source.get());
	//this->source->setStateSetModes(node->getOrCreateStateSet(), StateAttribute::ON);
}
