//
// Created by mathi on 30/10/2020.
//

#include "graphical/ASprite.hpp"

void Engine::ASprite::setTexture(std::shared_ptr<Engine::ATexture> &texture)
{
    _texture = texture;
}
