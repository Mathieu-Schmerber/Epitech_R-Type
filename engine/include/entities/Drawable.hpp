//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_DRAWABLE_HPP
#define RTYPE_DRAWABLE_HPP

#include "ecs/Entity.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"

namespace Engine {

    class Drawable : public Engine::Entity {
        public:
            explicit Drawable(const Point<int> &pos, std::unique_ptr<Engine::ASprite> spr, int layer = 0) : Engine::Entity()
            {
             this->addComponent<TransformComponent>(pos);
             this->addComponent<SpriteComponent>(layer, std::move(spr));
            }
    };
}

#endif //RTYPE_DRAWABLE_HPP
