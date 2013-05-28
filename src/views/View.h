#ifndef PH_VIEW_H
#define PH_VIEW_H

#include <osgViewer/Viewer>

using namespace osgViewer;

namespace ph {
    class View : public Viewer {
        public:
            virtual void switchToMainPerspective() = 0;
            virtual void switchToSecondPerspective() = 0;
            virtual void switchToThirdPerspective() = 0;
    }; 
}

#endif
