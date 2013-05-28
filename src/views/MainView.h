#ifndef PH_MAIN_VIEW_H
#define PH_MAIN_VIEW_H

#include "View.h"

namespace ph {
      class MainView : public ph::View {
        public:
            MainView();
            virtual void switchToMainPerspective();
            virtual void switchToSecondPerspective();
            virtual void switchToThirdPerspective();
    };
}

#endif
