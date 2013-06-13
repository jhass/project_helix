#ifndef PH_MAIN_VIEW_H
#define PH_MAIN_VIEW_H

#include <osgViewer/View>

namespace ph {
      class MainView : public osgViewer::View {
        public:
            MainView();
            void switchToMainPerspective();
            void switchToSecondPerspective();
            void switchToThirdPerspective();
    };
}

#endif
