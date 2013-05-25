#ifndef VIEW_H
#define VIEW_H

#include <osgViewer/Viewer>

using namespace osgViewer;

namespace ph {
    class View : public Viewer {
        public:
            virtual void switchToMainPerspective() = 0;
            virtual void switchToSecondaryPerspective() = 0;
    }; 
}

#endif
