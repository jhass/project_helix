#ifndef PH_MAIN_SCENE_H
#define PH_MAIN_SCENE_H

#include <osg/Group>

#include "objects/Ship.h"
#include <animation/ShipNodeCallback.h>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>

using namespace osg;

namespace ph {
    class MainScene : public Group {
        private:
            ref_ptr<osgShadow::ShadowedScene> ss;
            ref_ptr<Group> main;
            Node* addTransformedNode(Node* node, const Matrix& matrix);
            void createSkyboxAndSuns();
            void createPlanet();
            void createStation();
            void createShip();
            void createAsteroidField();
            void createComet();
            void createCuboid();
            void createReaper();
            void createNebula();
        public:
            MainScene();
            ref_ptr<ph::Ship> ship;
    };
}

#endif
