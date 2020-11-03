//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_COLLIDERCOMPONENT_HPP
#define RTYPE_COLLIDERCOMPONENT_HPP

#include "ecs/Entity.hpp"

namespace Engine {

    class ColliderComponent : public Engine::Component {
    private:
        std::vector<std::shared_ptr<Engine::Entity>> _collisions;

    public:
        explicit ColliderComponent() : Component() {}

        void clearCollisions() {this->_collisions.clear();};
        void collide(std::shared_ptr<Entity> &entity) {_collisions.emplace_back(entity);}

        [[nodiscard]] std::vector<std::shared_ptr<Engine::Entity>> getCollisions() const {
            return this->_collisions;
        }
    };
}

#endif //RTYPE_COLLIDERCOMPONENT_HPP