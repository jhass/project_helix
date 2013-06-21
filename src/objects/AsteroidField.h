#ifndef PH_ASTEROID_FIELD_H
#define PH_ASTEROID_FIELD_H

#include <osg/Group>

using namespace osg;

namespace ph {
    class AsteroidField : public Group {
        private:
            ref_ptr<Group> base_field;
            Node* addToBaseField(Node* node, const Matrix& matrix);
            void createBaseField();
            void addBaseField(const Matrix& matrix);
            void buildFullField();
        public:
            AsteroidField();
    };
}

#endif
