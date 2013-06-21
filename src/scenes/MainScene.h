#ifndef PH_MAIN_SCENE_H
#define PH_MAIN_SCENE_H

#include <osg/Group>

#include "objects/Ship.h"
#include <animation/ShipNodeCallback.h>
#include <osgShadow/ShadowedScene>

using namespace osg;

namespace ph {
    class MainScene : public Group {
        private:
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
        protected:
            ref_ptr<osgShadow::ShadowedScene> shadowedScene;
        public:
            MainScene();
            MainScene(Group* shadowedScene);
            ref_ptr<ph::Ship> ship;
    };
}

#endif
