#include "views/MainView.h"
#include "interactors/KeyboardEventHandler.h"

using namespace osg;

int main(void) {
    ref_ptr<ph::View> view = new ph::MainView();
    new ph::KeyboardEventHandler(view.get());

    return view->run();
}
