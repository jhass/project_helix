#include <osgViewer/CompositeViewer>

#include "views/MainView.h"
#include "views/CockpitView.h"
#include "interactors/KeyboardEventHandler.h"


using namespace osg;
using namespace osgViewer;

int main(void) {
    srand(time(NULL)); // initialize pseudo random number generator

    ref_ptr<CompositeViewer> viewer = new CompositeViewer();

    ref_ptr<ph::MainView> mainView = new ph::MainView();
    ref_ptr<ph::CockpitView> cockpitView = new ph::CockpitView(mainView->getScene());
    ref_ptr<ph::KeyboardEventHandler> handler = new ph::KeyboardEventHandler(mainView.get());
    cockpitView->addEventHandler(handler.get());

    unsigned int width, height;
    GraphicsContext::WindowingSystemInterface* wsi = GraphicsContext::getWindowingSystemInterface();
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);

    // setup window properties
    ref_ptr<GraphicsContext::Traits> traits = new GraphicsContext::Traits;
    traits->x = 0;
    traits->y = 0;
    traits->width = width;
    traits->height = height;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;

    ref_ptr<GraphicsContext> context = GraphicsContext::createGraphicsContext(traits.get());
    cockpitView->getCamera()->setGraphicsContext(context.get());
    mainView->getCamera()->setGraphicsContext(context.get());

    cockpitView->getCamera()->setViewport(new Viewport(0, 0, width, height));
    viewer->addView(cockpitView);    

    //                                                  x,           y 
    mainView->getCamera()->setViewport(new Viewport(width-20-width/4, 20,
    //                                                  width,    height
                                                    width/4, height/4));
    viewer->addView(mainView);

    return viewer->run();
}
