/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include <iostream>
#include "sfml/SpriteSfml.hpp"
#include "sfml/WindowSFML.hpp"

void SpriteSFML::loadFromFile(const std::string filename)
{
    if (_texture.loadFromFile(filename)) {
        _sprite.setTexture(_texture);
    } else {
        std::cerr << "\033[33mTexture WARNING : Invalid load of texture " << filename << "\033[0m" << std::endl;
    }
}

void SpriteSFML::setScale(Engine::Scale<float> scale)
{
    _sprite.setScale(scale.x, scale.y);
}

Engine::Scale<float> SpriteSFML::getScale() const
{
    return {_sprite.getScale().x, _sprite.getScale().y};
}

void SpriteSFML::setPosition(Engine::Point<float> position)
{
    _sprite.setPosition(position.x, position.y);
}

Engine::Point<float> SpriteSFML::getPosition() const
{
    return {_sprite.getPosition().x, _sprite.getPosition().y};
}

void SpriteSFML::setOrigin(Engine::Point<float> origin)
{
    _sprite.setOrigin(origin.x, origin.y);
}

Engine::Point<float> SpriteSFML::getOrigin() const
{
    return {_sprite.getOrigin().x, _sprite.getOrigin().y};
}

void SpriteSFML::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle)
{
    std::shared_ptr<WindowSFML> windowSFML = std::dynamic_pointer_cast<WindowSFML>(window);

    setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    setRotation(angle);
    windowSFML->getWindow()->draw(_sprite);
}

void SpriteSFML::setRotation(float angle)
{
    _sprite.setRotation(angle);
}

float SpriteSFML::getRotation()
{
    return _sprite.getRotation();
}

Engine::Size<int> SpriteSFML::getSize()
{
    return {static_cast<int>(_sprite.getGlobalBounds().width), static_cast<int>(_sprite.getGlobalBounds().height)};
}
