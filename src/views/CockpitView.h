#ifndef PH_COCKPIT_VIEW
#define PH_COCKPIT_VIEW

#include <osgViewer/View>

#include "scenes/MainScene.h"

namespace ph {
    class CockpitView : public osgViewer::View {
        public:
            CockpitView(MainScene* scene);
    };
}

#endif
