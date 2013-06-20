#ifndef PH_MISSILE_H
#define PH_MISSILE_H

#include <string>

#include <osg/Geode>
#include <osg/Node>

using namespace osg;


namespace ph {
    
	class Missile : public Group {
        private:
          
            ref_ptr<Node> missile;

  
          
        public:
            Missile();
            ~Missile();
           
    };
}

#endif
