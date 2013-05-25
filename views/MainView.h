#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "View.h"

namespace ph {
      class MainView : public ph::View {
        public:
            MainView();
            virtual void switchToMainPerspective();
            virtual void switchToSecondaryPerspective();
    };
}

#endif
