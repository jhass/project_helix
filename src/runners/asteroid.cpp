#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>

#include "objects/Asteroid.h"

using namespace osg;

int main(void) {
    // main Element
    ref_ptr<Group> root = new Group();

    // asteroid_standard(radius, lengthSteps, widthSteps, deformationfactor in x,y,z)
    // Big main asteroids
    ref_ptr<ph::Asteroid> asteroid_main_fine = new ph::Asteroid(12, 20, 20, 1, 1, 1);
    
    // getting the big asteroids to its place
    ref_ptr<MatrixTransform> trans_main_01 = new MatrixTransform;
    trans_main_01->setMatrix(Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(55.0, -30.0, -3.0));
    trans_main_01->addChild(asteroid_main_fine.get());
    
    // giving the big asteroids to root
    root->addChild(asteroid_main_fine.get());
    root->addChild(trans_main_01.get());
    
    // small asteroids
    ref_ptr<ph::Asteroid> asteroid_small_crude = new ph::Asteroid(3, 5, 5, 1, 1, 1);
    ref_ptr<ph::Asteroid> asteroid_small_fine = new ph::Asteroid(3, 20, 20, 1, 1, 1);
    
    // getting the small asteroids to its place
    ref_ptr<MatrixTransform> trans_small_01 = new MatrixTransform;
    trans_small_01->setMatrix(Matrix::translate(-5.0, 20.0, 7.0));
    trans_small_01->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_02 = new MatrixTransform;
    trans_small_02->setMatrix(Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(30.0, -3.0, 7.0));
    trans_small_02->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_03 = new MatrixTransform;
    trans_small_03->setMatrix(Matrix::rotate(PI_2,Vec3(1.0,0.0,1.0))*Matrix::translate(35.0, 3.0, 2.0));
    trans_small_03->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_04 = new MatrixTransform;
    trans_small_04->setMatrix(Matrix::translate(31.0, 12.0, 3.0));
    trans_small_04->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_05 = new MatrixTransform;
    trans_small_05->setMatrix(Matrix::translate(31.0, 14.0, 3.0));
    trans_small_05->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_06 = new MatrixTransform;
    trans_small_06->setMatrix(Matrix::translate(7.0, 22.0, -4.0));
    trans_small_06->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_07 = new MatrixTransform;
    trans_small_07->setMatrix(Matrix::translate(-5.0, -25.0, -4.0));
    trans_small_07->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_08 = new MatrixTransform;
    trans_small_08->setMatrix(Matrix::translate(80, -6.0, 16.0));
    trans_small_08->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_09 = new MatrixTransform;
    trans_small_09->setMatrix(Matrix::translate(72, -16.0, 10.0));
    trans_small_09->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_10 = new MatrixTransform;
    trans_small_10->setMatrix(Matrix::translate(60.0, 13.0, -12.0));
    trans_small_10->addChild(asteroid_small_crude.get());
    
    ref_ptr<MatrixTransform> trans_small_11 = new MatrixTransform;
    trans_small_11->setMatrix(Matrix::translate(28.0, -17.0, 5.0));
    trans_small_11->addChild(asteroid_small_fine.get());
    
    ref_ptr<MatrixTransform> trans_small_12 = new MatrixTransform;
    trans_small_12->setMatrix(Matrix::translate(20.0, -20.0, 0.0));
    trans_small_12->addChild(asteroid_small_crude.get());
    
    // giving the small astroids to root
    root->addChild(trans_small_01.get());
    root->addChild(trans_small_02.get());
    root->addChild(trans_small_03.get());
    root->addChild(trans_small_04.get());
    root->addChild(trans_small_05.get());
    root->addChild(trans_small_06.get());
    root->addChild(trans_small_07.get());
    root->addChild(trans_small_08.get());
    root->addChild(trans_small_09.get());
    root->addChild(trans_small_10.get());
    root->addChild(trans_small_11.get());
    root->addChild(trans_small_12.get());
    
    // flat asteroids
    ref_ptr<ph::Asteroid> asteroid_flat_fine = new ph::Asteroid(5, 20, 20, 2, 3, 1);
    ref_ptr<ph::Asteroid> asteroid_flat_crude = new ph::Asteroid(5, 5, 5, 1, 1, 4);
    ref_ptr<ph::Asteroid> asteroid_flat_small = new ph::Asteroid(2, 5, 5, 4, 1, 1);
    
    // getting the small asteroids to its place
    ref_ptr<MatrixTransform> trans_flat_01 = new MatrixTransform;
    trans_flat_01->setMatrix(Matrix::rotate(PI_4,Vec3(0.0,0.0,1.0))*Matrix::translate(76.0, 3.0, -2.0));
    trans_flat_01->addChild(asteroid_flat_fine.get());
    
    ref_ptr<MatrixTransform> trans_flat_02 = new MatrixTransform;
    trans_flat_02->setMatrix(Matrix::translate(50.0, 7.0, -2.0));
    trans_flat_02->addChild(asteroid_flat_crude.get());
    
    ref_ptr<MatrixTransform> trans_flat_03 = new MatrixTransform;
    trans_flat_03->setMatrix(Matrix::rotate(PI_4,Vec3(1.0,0.0,1.0))*Matrix::translate(-22.0, 7.0, -2.0));
    trans_flat_03->addChild(asteroid_flat_small.get());
    
    // giving the flat asteroids to root
    root->addChild(trans_flat_01.get());
    root->addChild(trans_flat_02.get());
    root->addChild(trans_flat_03.get());
    
    // giving the asteroids a texture
    asteroid_main_fine->setTexture(0, "../resources/phobos.jpg");
    asteroid_flat_crude->setTexture(0, "../resources/ceres.jpg");
    asteroid_flat_fine->setTexture(0, "../resources/ceres.jpg");
    asteroid_flat_small->setTexture(0, "../resources/phobos.jpg");
    asteroid_small_crude->setTexture(0, "../resources/ceres.jpg");
    asteroid_small_fine->setTexture(0, "../resources/phobos.jpg");
    
    // enables PolygonMode
    ref_ptr<PolygonMode> pm = new PolygonMode;
    pm->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
    //root->getOrCreateStateSet()->setAttribute(pm.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
