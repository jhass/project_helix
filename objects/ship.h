#ifndef SHIP_H
#define SHIP_H

#include <osgDB/ReadFile>
#include <string>

using namespace osg;

class Ship : public Group {
    private:
        static std::string fileLocation;
        
    public: 
        Ship();
        ~Ship();

};

#endif
