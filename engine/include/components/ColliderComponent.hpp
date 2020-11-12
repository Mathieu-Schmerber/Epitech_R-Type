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
        Engine::Box<float> _hitBox;
        Engine::Box<float> _baseHitBox;
        std::vector<std::shared_ptr<Engine::Entity>> _collisions;

    public:
        explicit ColliderComponent() : _collisionMask(0), _isActive(false), _hitBox(0, 0, 0, 0), _baseHitBox(0, 0, 0, 0),
                                       Engine::Component() {}

        explicit ColliderComponent(int mask, const Engine::Box<float> &box) : _collisionMask(mask), _hitBox(box),
                                                                               _isActive(true), _baseHitBox(box),
                                                                               Engine::Component() {}

        explicit ColliderComponent(int mask, const Engine::Point<float> &pos, const Engine::Point<float> &size)
        : _collisionMask(mask), _isActive(true), _hitBox(0, 0, 0, 0), _baseHitBox(0,0,0,0), Engine::Component()
        {
            this->_hitBox = {{(float) pos.x,  (float) pos.y},{(float) size.x, (float) size.y}};
            this->_baseHitBox = {{(float) pos.x,  (float) pos.y},{(float) size.x, (float) size.y}};
        }

        void clearCollisions() { this->_collisions.clear(); };

        void collide(std::shared_ptr<Entity> &entity) {
            if (this->_isActive)
                _collisions.emplace_back(entity);
        }

        void setBaseHitBox(const Engine::Box<float> &box) { this->_baseHitBox = box; }
        [[nodiscard]] Engine::Box<float> getBaseHitBox() const { return this->_baseHitBox; }
        void setHitBox(const Engine::Box<float> &box) { this->_hitBox = box; }
        [[nodiscard]] Engine::Box<float> getHitBox() const { return this->_hitBox; }

        void setActive(bool active) { this->_isActive = active; }

        void setCollisionMask(int mask) { this->_collisionMask = mask; }

        [[nodiscard]] int getCollisionMask() const { return this->_collisionMask; }

        [[nodiscard]] std::vector<std::shared_ptr<Engine::Entity>> getCollisions() const {
            return this->_collisions;
        }
    };
}

#endif //RTYPE_COLLIDERCOMPONENT_HPP