/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "graphical/AText.hpp"

void Engine::AText::setFont(std::shared_ptr<Engine::AFont> &font)
{
    _font = font;
}

std::shared_ptr<Engine::AFont> Engine::AText::getFont() const
{
    return _font;
}
