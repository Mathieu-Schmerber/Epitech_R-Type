//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_TEXT_HPP
#define RTYPE_TEXT_HPP

#include "components/TextComponent.hpp"
#include "components/TransformComponent.hpp"
#include "ecs/Entity.hpp"

namespace Engine {
    class Text : public Engine::Entity {
        public:
        explicit Text(const Point<int> &pos, std::unique_ptr<Engine::AText> text, int layer = 0) : Engine::Entity()
        {
            this->addComponent<TransformComponent>(pos);
            this->addComponent<TextComponent>(layer, std::move(text));
        }
    };
}

#endif //RTYPE_TEXT_HPP