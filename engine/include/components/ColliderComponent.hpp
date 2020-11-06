//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_COLLIDERCOMPONENT_HPP
#define RTYPE_COLLIDERCOMPONENT_HPP

#include "ecs/Entity.hpp"

namespace Engine {

    class ColliderComponent : public Engine::Component {
    private:
        int _collisionMask;
        bool _isActive;
        std::vector<std::shared_ptr<Engine::Entity>> _collisions;

    public:
        explicit ColliderComponent() : _collisionMask(0), _isActive(false), Engine::Component() {}
        explicit ColliderComponent(int mask) : _collisionMask(mask), _isActive(true), Engine::Component() {}

        void clearCollisions() {this->_collisions.clear();};

        void collide(std::shared_ptr<Entity> &entity) {
            if (this->_isActive)
                _collisions.emplace_back(entity);
        }

        void setActive(bool active) {this->_isActive = active;}
        void setCollisionMask(int mask) {this->_collisionMask = mask;}

        [[nodiscard]] int getCollisionMask() const {return this->_collisionMask;}

        [[nodiscard]] std::vector<std::shared_ptr<Engine::Entity>> getCollisions() const {
            return this->_collisions;
        }
    };
}

#endif //RTYPE_COLLIDERCOMPONENT_HPP