#ifndef PH_CHRONOS_STATION_H
#define PH_CHRONOS_STATION_H

#include <string>

#include <osg/Node>
#include <osg/Geode>

using namespace osg;

namespace ph {
    class Chronos : public Group {
        private:
            //static string fileLocation;
            ref_ptr<Node> station;

        public: 
            Chronos();
    };
}
#endif
