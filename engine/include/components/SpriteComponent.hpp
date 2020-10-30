//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_SPRITECOMPONENT_HPP
#define RTYPE_SPRITECOMPONENT_HPP

#include "ASprite.hpp"
#include "Component.hpp"

class SpriteComponent : public Engine::Component
{
private:
    Engine::ASprite *_sprite;

public:
    SpriteComponent(Engine::ASprite *sprite);

    Engine::ASprite *getSprite() const;
    void setSprite(Engine::ASprite *sprite);
};

#endif //RTYPE_SPRITECOMPONENT_HPP
