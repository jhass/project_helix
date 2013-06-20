#ifndef PH_MAIN_VIEW_H
#define PH_MAIN_VIEW_H

#include <osgViewer/View>

#include "scenes/MainScene.h"

namespace ph {
      class MainView : public osgViewer::View {
        private:
            ref_ptr<MainScene> scene;
        public:
            MainView();
            MainScene* getScene();
            void switchToMainPerspective();
            void switchToSecondPerspective();
            void switchToThirdPerspective();
            void yawShipLeft();
            void yawShipRight();
            void pitchShipUp();
            void pitchShipDown();
            void shipTurboOn();
            void shipTurboOff();
    };
}

#endif
