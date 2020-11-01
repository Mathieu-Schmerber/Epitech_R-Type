//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_SPRITECOMPONENT_HPP
#define RTYPE_SPRITECOMPONENT_HPP

#include "Graphical/ASprite.hpp"
#include "ecs/Component.hpp"
#include <memory>

namespace Engine {

    class SpriteComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::ASprite> _sprite;

    public:
        explicit SpriteComponent(std::unique_ptr<Engine::ASprite> sprite = nullptr) : _sprite(std::move(sprite)) {};

        std::unique_ptr<Engine::ASprite> &getSprite() {return this->_sprite;}
        void setDisplay(std::unique_ptr<Engine::ASprite> sprite) { this->_sprite = std::move(sprite);}
    };
}

#endif //RTYPE_SPRITECOMPONENT_HPP
