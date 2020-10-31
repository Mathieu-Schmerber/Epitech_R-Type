//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_BUTTON_HPP
#define RTYPE_BUTTON_HPP

#include "ecs/Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

class Button : public Engine::Entity
{
public:
    explicit Button(const std::pair<int, int> &pos) : Engine::Entity()
    {
        this->addComponent<TransformComponent>(pos);
        this->addComponent<SpriteComponent>();
    }
};


#endif //RTYPE_BUTTON_HPP
