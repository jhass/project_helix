#ifndef SHIP_H
#define SHIP_H

#include <string>

#include <osg/ProxyNode>

using namespace osg;
using namespace std;

namespace ph {
    class Ship : public ProxyNode {
        private:
            static string fileLocation;

        public: 
            Ship();
    };
}

#endif
