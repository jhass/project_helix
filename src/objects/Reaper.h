#ifndef PH_REAPER_H
#define PH_REAPER_H

#include <string>

#include <osg/Node>
#include <osg/Geode>

using namespace osg;

namespace ph {
    class Reaper : public Group {
        private:
            static std::string fileLocation;
            ref_ptr<Node> reaper;

        public: 
            Reaper();
    };
}
#endif
