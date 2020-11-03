/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/TextureSFML.hpp"

void TextureSFML::loadFromFile(const std::string filename)
{
    if (!_texture->loadFromFile(filename))
        std::cerr << "\033[33mTexture WARNING : Invalid load of texture " << filename << "\033[0m" << std::endl;
}

std::shared_ptr<sf::Texture> &TextureSFML::getTexture()
{
    return _texture;
}