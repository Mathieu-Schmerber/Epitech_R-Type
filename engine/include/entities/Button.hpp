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

namespace Engine {

    class Button : public Engine::Entity {
    public:
        Button(const Point<int> &pos,
              std::unique_ptr<Engine::ASprite> sprite,
              void (*onClick)(std::shared_ptr<Engine::AScene> &),
               std::shared_ptr<Engine::AScene> arg,
               const std::map<std::string, std::vector<Box<int>>> &anim = {}) : Engine::Entity()
        {
            this->addComponent<TransformComponent>(pos);
            this->addComponent<SpriteComponent>(std::move(sprite));
            this->addComponent<ClickableComponent>(onClick, arg);
            this->addComponent<AnimationComponent>(anim);
        }
    };

}


#endif //RTYPE_BUTTON_HPP
