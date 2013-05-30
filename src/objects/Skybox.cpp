#include <osg/MatrixTransform>

#include "Skybox.h"

// Konstruktor zum Anlegen der Skybox
ph::Skybox::Skybox(const int height, const int width) {
    // Übergeben der Länge/Breite
    this->height = height;
    this->width = width;
    
    // Anlegen der Rechtecke
    createRectangles();
}

void ph::Skybox::createRectangles() {

    // creating and placing front-Rectangle
    this->front = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_front = new MatrixTransform();
    rec_trans_front->setMatrix( Matrix::translate(0.0f, this->height/2.0, 0.0f) );
    rec_trans_front->addChild(this->front.get());
    this->addChild(rec_trans_front.get());
    
    // creating and placing back-Rectangle
    this->back = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_back = new MatrixTransform();
    rec_trans_back->setMatrix( Matrix::translate(0.0, (-1.0)*this->height/2.0, 0.0f));
    rec_trans_back->addChild(this->front.get());
    this->addChild(rec_trans_back.get());
    
    // creating and placing left-Rectangle
    this->left = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_left = new MatrixTransform();
    rec_trans_left->setMatrix(Matrix::translate(0.0f, this->height/2.0, 0.0f)*
                            Matrix::rotate(3*PI_2,Vec3(0.0,0.0,1.0)));
    rec_trans_left->addChild(this->left.get());    
    this->addChild(rec_trans_left.get());
    
    // creating and placing right-Rectangle
    this->right = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_right = new MatrixTransform();
    rec_trans_right->setMatrix(Matrix::translate(0.0f, (-1.0)*this->height/2.0, 0.0f)*
                            Matrix::rotate(-PI_2,Vec3(0.0,0.0,1.0)));
    rec_trans_right->addChild(this->right.get());    
    this->addChild(rec_trans_right.get());
    
    // creating and placing top-Rectangle
    this->top = new Rectangle(this->height, this->height);
    ref_ptr<MatrixTransform> rec_trans_top = new MatrixTransform();
    rec_trans_top->setMatrix(Matrix::translate(0.0, this->width/2.0,0.0)*
                            Matrix::rotate(PI_2,Vec3(1.0,0.0,0.0)));
    rec_trans_top->addChild(this->top.get());    
    this->addChild(rec_trans_top.get());
    
    // creating and placing bottom-Rectangle
    this->bottom = new Rectangle(this->height, this->height);
    ref_ptr<MatrixTransform> rec_trans_bottom = new MatrixTransform();
    rec_trans_bottom->setMatrix(Matrix::translate(0.0, (-1.0)*this->width/2.0,0.0)*
                            Matrix::rotate(PI_2,Vec3(1.0,0.0,0.0)));
    rec_trans_bottom->addChild(this->bottom.get());    
    this->addChild(rec_trans_bottom.get());
}

void ph::Skybox::setTexture(const Position pos, const string filename) {
    // Rechteck aus Enum bestimmen.
    // Textur an Rechteck übergeben.
}
