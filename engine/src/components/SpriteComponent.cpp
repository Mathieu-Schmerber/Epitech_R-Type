//
// Created by mathi on 30/10/2020.
//

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(Engine::ASprite *sprite) : _sprite(sprite), Engine::Component() {}

Engine::ASprite *SpriteComponent::getSprite() const
{
    return this->_sprite;
}

void SpriteComponent::setSprite(Engine::ASprite *sprite)
{
    this->_sprite = sprite;
}
