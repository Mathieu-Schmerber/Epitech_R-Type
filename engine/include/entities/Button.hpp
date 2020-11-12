//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_BUTTON_HPP
#define RTYPE_BUTTON_HPP

#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/ButtonComponent.hpp"

namespace Engine {

    class Button : public Engine::Entity {
    public:
        Button(const Point<float> &pos, const Point<float> &size,
              std::unique_ptr<Engine::ASprite> sprite,
              void (*onClick)(std::shared_ptr<Engine::AScene> &),
               std::shared_ptr<Engine::AScene> arg,
               int layer = 1) : Engine::Entity()
        {
            this->addComponent<ColliderComponent>(0, pos, size);
            this->addComponent<TransformComponent>(pos);
            this->addComponent<SpriteComponent>(layer, std::move(sprite));
            this->addComponent<ClickableComponent>();
            this->addComponent<ButtonComponent>(onClick, arg);
            this->addComponent<AnimationComponent>();
        }
    };

}


#endif //RTYPE_BUTTON_HPP
