#ifndef PH_SHIP_VIEW
#define PH_SHIP_VIEW

#include <osgViewer/View>

#include "scenes/MainScene.h"

namespace ph {
    class ShipView : public osgViewer::View {
        public:
            ShipView(MainScene* scene);
    };
}

#endif
