#include "views/MainView.h"
#include "interactors/KeyboardEventHandler.h"

using namespace osg;

int main(void) {
    srand(time(NULL)); // initialize pseudo random number generator

    ref_ptr<ph::View> view = new ph::MainView();
    ref_ptr<ph::KeyboardEventHandler> handler = new ph::KeyboardEventHandler(view.get());

    return view->run();
}
