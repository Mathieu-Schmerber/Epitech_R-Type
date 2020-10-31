//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_SPRITECOMPONENT_HPP
#define RTYPE_SPRITECOMPONENT_HPP

#include "ASprite.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class SpriteComponent : public Engine::Component {
    private:
        Engine::ASprite *_sprite;

    public:
        explicit SpriteComponent(Engine::ASprite *sprite = nullptr);

        Engine::ASprite *getSprite() const{return this->_sprite;}
        void setSprite(Engine::ASprite *sprite){this->_sprite = sprite;}
    };
}

#endif //RTYPE_SPRITECOMPONENT_HPP
