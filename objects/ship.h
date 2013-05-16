#ifndef SHIP_H
#define SHIP_H

#include <osgDB/ReadFile>
#include <osg/ProxyNode>
#include <string>

using namespace osg;

class Ship : public ProxyNode {
    private:
        static std::string fileLocation;
        
    public: 
        Ship();

};

#endif
