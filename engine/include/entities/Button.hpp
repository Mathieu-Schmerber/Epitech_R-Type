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

namespace Engine {

    class Button : public Engine::Entity {
    public:
        Button(const Point<int> &pos,
              std::unique_ptr<Engine::ASprite> sprite, void (*onClick)(std::shared_ptr<Engine::AScene> &),
               std::shared_ptr<Engine::AScene> arg) : Engine::Entity()
        {
            this->addComponent<TransformComponent>(pos);
            this->addComponent<SpriteComponent>(std::move(sprite));
            this->addComponent<ClickableComponent>(onClick, arg);
        }
    };

}


#endif //RTYPE_BUTTON_HPP
