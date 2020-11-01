//
// Created by mathi on 30/10/2020.
//

#include "Graphical/ASprite.hpp"

Engine::ASprite::ASprite() : _size({0, 0}) {}

Engine::Point<int> Engine::ASprite::getSize()
{
    return this->_size;
}