#include <osg/MatrixTransform>
#include <osg/AnimationPath>

#include "Asteroid.h"
#include "util.h"

#include "AsteroidField.h"

ph::AsteroidField::AsteroidField() {
    createBaseField();
    buildFullField();
}


// Extends the created asteroid field by creating copies of one existing field
// and moving them to different directions based on pos(x,y,z)
void ph::AsteroidField::buildFullField() {
    addBaseField(Matrix::translate(0.0,0.0,30));
    addBaseField(Matrix::translate(200.0,0.0,0.0));
    addBaseField(Matrix::rotate(PI,Vec3(0.0,1.0,0.0)));
    addBaseField(Matrix::rotate(PI,Vec3(1.0,0.0,0.0))*Matrix::translate(-200.0,0.0,0.0));
    addBaseField(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(200.0,0.0,30));
    addBaseField(Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*Matrix::translate(-200.0,0.0,30));
}

void ph::AsteroidField::addBaseField(const Matrix& matrix) {
    ref_ptr<MatrixTransform> field = new MatrixTransform;
    field->addChild(base_field.get());
    field->setMatrix(matrix);
    this->addChild(field.get());
}

void ph::AsteroidField::createBaseField() {
    base_field = new Group;

    // asteroid_standard(radius, lengthSteps, widthSteps, deformationfactor in x,y,z)

    // Big main asteroids
    ref_ptr<ph::Asteroid> asteroid_main_fine = new ph::Asteroid(12, 20, 20, 1, 1, 1);
    asteroid_main_fine->setTexture(0, "../resources/phobos.jpg");
    base_field->addChild(asteroid_main_fine.get());
    addToBaseField(asteroid_main_fine.get(),
        Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(55.0, -30.0, -3.0));
    
    // small asteroids
    ref_ptr<ph::Asteroid> asteroid_small_fine = new ph::Asteroid(3, 20, 20, 1, 1, 1);
    asteroid_small_fine->setTexture(0, "../resources/phobos.jpg");
    addToBaseField(asteroid_small_fine.get(),
        Matrix::translate(31.0, 12.0, 3.0));
    addToBaseField(asteroid_small_fine.get(),
        Matrix::translate(31.0, 14.0, 3.0));
    addToBaseField(asteroid_small_fine.get(),
        Matrix::translate(7.0, 22.0, -4.0));
    addToBaseField(asteroid_small_fine.get(),
        Matrix::translate(-5.0, -25.0, -4.0));

    ref_ptr<ph::Asteroid> asteroid_small_crude = new ph::Asteroid(3, 5, 5, 1, 1, 1);
    asteroid_small_crude->setTexture(0, "../resources/ceres.jpg");
    addToBaseField(asteroid_small_crude.get(),
        Matrix::translate(-5.0, 20.0, 7.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::rotate(PI_2,Vec3(0.0,1.0,1.0))*Matrix::translate(30.0, -3.0, 7.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::rotate(PI_2,Vec3(1.0,0.0,1.0))*Matrix::translate(35.0, 3.0, 2.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::translate(80, -6.0, 16.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::translate(72, -16.0, 10.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::translate(60.0, 13.0, -12.0));
    addToBaseField(asteroid_small_fine.get(),
        Matrix::translate(28.0, -17.0, 5.0));
    addToBaseField(asteroid_small_crude.get(),
        Matrix::translate(20.0, -20.0, 0.0));
    
    
    // flat asteroids
    ref_ptr<ph::Asteroid> asteroid_flat_fine = new ph::Asteroid(5, 20, 20, 2, 3, 1);
    asteroid_flat_fine->setTexture(0, "../resources/ceres.jpg");
    ref_ptr<Node> flat_fine = addToBaseField(asteroid_flat_fine.get(),
        Matrix::rotate(PI_4,Vec3(0.0,0.0,1.0))*Matrix::translate(76.0, 3.0, -2.0));

    ref_ptr<ph::Asteroid> asteroid_flat_crude = new ph::Asteroid(5, 5, 5, 1, 1, 4);
    asteroid_flat_crude->setTexture(0, "../resources/ceres.jpg");
    addToBaseField(asteroid_flat_crude.get(),
        Matrix::translate(50.0, 7.0, -2.0));

    ref_ptr<ph::Asteroid> asteroid_flat_small = new ph::Asteroid(2, 5, 5, 4, 1, 1);
    asteroid_flat_small->setTexture(0, "../resources/phobos.jpg");
    ref_ptr<Node> flat_small = addToBaseField(asteroid_flat_small.get(),
        Matrix::rotate(PI_4,Vec3(1.0,0.0,1.0))*Matrix::translate(-22.0, 7.0, -2.0));
    
    
    
    // Creating animation; Rotation of some asteroids
    osg::ref_ptr<osg::AnimationPathCallback> flat_fine_animation = new osg::AnimationPathCallback;
    flat_fine_animation->setAnimationPath(
        ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Y_AXIS,
                                NULL, 0, 76, NULL, 0, 3, NULL, 0, -2)
    );
    flat_fine->setUpdateCallback(flat_fine_animation.get());

    osg::ref_ptr<osg::AnimationPathCallback> flat_small_animation = new osg::AnimationPathCallback;
    flat_small_animation->setAnimationPath(
        ph::createAnimationPath(60.0f, 2*PI, ph::LOOP, ph::POS_Y_AXIS,
                                NULL, 0, -22, NULL, 0, 7, NULL, 0, -2)
    );
    flat_small->setUpdateCallback(flat_small_animation.get());
}


Node* ph::AsteroidField::addToBaseField(Node* node, const Matrix& matrix) {
    ref_ptr<MatrixTransform> transform = new MatrixTransform;
    transform->addChild(node);
    transform->setMatrix(matrix);
    base_field->addChild(transform);
    return transform.release();
}
