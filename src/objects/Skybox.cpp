#include <osg/MatrixTransform>

#include "Skybox.h"

// Konstruktor zum Anlegen der Skybox
ph::Skybox::Skybox(const int height, const int width) {
    // Übergeben der Länge/Breite
    this->height = height;
    this->width = width;
    
    setReferenceFrame(Transform::ABSOLUTE_RF);
    setCullingActive(false);
    
    osg::StateSet* stateSet = getOrCreateStateSet();
    // Tiefenpuffer; Objekte verschwinden nicht einfach, wenn sich auf Rand
    // der Skybox treffen
    stateSet->setAttributeAndModes(new Depth(Depth::LEQUAL, 1.0f, 1.0f));
    // Licht ausmachen
    stateSet->setMode(GL_LIGHTING, StateAttribute::OFF);
    // Culling für Flächen außerhalb der Skybox
    stateSet->setMode(GL_CULL_FACE, StateAttribute::OFF);
    //ss->setRenderBinDetails( 5, "RenderBin" );
    
    // Anlegen der Rechtecke
    createRectangles();
}

void ph::Skybox::createRectangles() {

    /* Rotationen werde so durchgeführt, dass man vom Mittelpunkt der Box aus jeweils korrekte
       Sicht auf die Texturen hat, also (0,0) "unten links" ist und (1,1) "oben rechts" */

    // creating and placing front-Rectangle
    this->front = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_front = new MatrixTransform();
    // verschieben um hoehe/2 in y
    rec_trans_front->setMatrix( Matrix::translate(0.0, this->height/2.0, 0.0));
    rec_trans_front->addChild(this->front.get());
    this->addChild(rec_trans_front.get());
    
    // creating and placing back-Rectangle
    this->back = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_back = new MatrixTransform();
    // zuerst rotieren. pi um z, dann verschieben um -hoehe/2 in y
    rec_trans_back->setMatrix( Matrix::rotate(PI,Vec3(0.0,0.0,1.0))*
                        Matrix::translate(0.0, -this->height/2.0, 0.0));
    rec_trans_back->addChild(this->back.get());
    this->addChild(rec_trans_back.get());
    
    // creating and placing left-Rectangle
    this->left = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_left = new MatrixTransform();
    // zuerst rotieren: pi/2 um z, dann verschieben um -hoehe/2 in x
    rec_trans_left->setMatrix( Matrix::rotate(PI_2,Vec3(0.0,0.0,1.0))*
                        Matrix::translate(-this->height/2.0, 0.0, 0.0));
    rec_trans_left->addChild(this->left.get());    
    this->addChild(rec_trans_left.get());
    
    // creating and placing right-Rectangle
    this->right = new Rectangle(this->height, this->width);
    ref_ptr<MatrixTransform> rec_trans_right = new MatrixTransform();
    // zuerst rotieren: -pi/2 um z, dann verschieben um hoehe/2 in x
    rec_trans_right->setMatrix( Matrix::rotate(-PI_2,Vec3(0.0,0.0,1.0))*
                        Matrix::translate(this->height/2.0, 0.0, 0.0));
    rec_trans_right->addChild(this->right.get());    
    this->addChild(rec_trans_right.get());
    
    // creating and placing top-Rectangle
    this->top = new Rectangle(this->height, this->height);
    ref_ptr<MatrixTransform> rec_trans_top = new MatrixTransform();
    // zuerst rotieren: pi/2 um x, dann verschieben um breite/2 in z
    rec_trans_top->setMatrix( Matrix::rotate(PI_2,Vec3(1.0,0.0,0.0))*
                        Matrix::translate(0.0, 0.0, this->width/2.0));
    rec_trans_top->addChild(this->top.get());    
    this->addChild(rec_trans_top.get());
    
    // creating and placing bottom-Rectangle
    this->bottom = new Rectangle(this->height, this->height);
    ref_ptr<MatrixTransform> rec_trans_bottom = new MatrixTransform();
    // zuerst rotieren: -pi/2 um x, dann verschieben um -breite/2 in z
    rec_trans_bottom->setMatrix( Matrix::rotate(-PI_2,Vec3(1.0,0.0,0.0))*
                        Matrix::translate(0.0, 0.0, -this->width/2.0));
    rec_trans_bottom->addChild(this->bottom.get());    
    this->addChild(rec_trans_bottom.get());
}

// setting texture on the rectangle given bei the Position enumeration
void ph::Skybox::setTexture(const Position pos, const int textureNumber, const string filename) {
    Rectangle* rec;
    switch (pos) {
    case FRONT: rec = this->front; break;
    case BACK: rec = this->back; break;
    case TOP: rec = this->top; break;
    case BOTTOM: rec = this->bottom; break;
    case LEFT: rec = this->left; break;
    case RIGHT: rec = this->right;break;
    }
    
    rec->setTexture(textureNumber,filename);
}

// clamping an object to the skybox
void ph::Skybox::clampObjectToSkybox(ref_ptr<MatrixTransform>& mt) {
    this->addChild(mt.get());
}

/* aus: OSG Cookbook, pp. 256ff, Funktionen für Funktionalität: Verschieben der Skybox 
   geerbte Funktionen aus der Superklasse Transform zum Verschieben der Skybox mit 
   dem Auge */
bool ph::Skybox::computeLocalToWorldMatrix( Matrix& matrix, NodeVisitor* nv ) const
{
    if ( nv && nv->getVisitorType() == NodeVisitor::CULL_VISITOR )
    {
        osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>( nv );
        matrix.preMult( Matrix::translate(cv->getEyeLocal()) );
        return true;
    }
    else
        return Transform::computeLocalToWorldMatrix( matrix, nv );
}


bool ph::Skybox::computeWorldToLocalMatrix( Matrix& matrix, NodeVisitor* nv ) const
{
    if ( nv && nv->getVisitorType() == NodeVisitor::CULL_VISITOR )
    {
        osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>( nv );
        matrix.postMult( Matrix::translate(-cv->getEyeLocal()) );
        return true;
    }
    else
        return Transform::computeWorldToLocalMatrix( matrix, nv );
}
