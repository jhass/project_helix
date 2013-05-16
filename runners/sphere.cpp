#include "../objects/sphere.h"

int main( int argc, char** argv )
{
  // baue Geometry
  ref_ptr<Geometry> geom = createSphere(5,100,100);

  // baue Gemetrie-Knoten
    ref_ptr<Geode> model = new Geode;
    model->addDrawable(geom.get());


    ref_ptr<MatrixTransform> root = new MatrixTransform;
    root->setMatrix(Matrix::rotate(PI_2,Vec3(1,0,0)));
    root->addChild( model.get() );

   // wenn man die Dreiecke mal sehen will:
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    root->getOrCreateStateSet()->setAttribute (pm.get());

  osgViewer::Viewer viewer;
  viewer.setSceneData( root.get() );
  return viewer.run();
}
