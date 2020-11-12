/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/SpriteSfml.hpp"
#include "sfml/WindowSFML.hpp"
#include "sfml/TextureSFML.hpp"

void SpriteSFML::setTexture(std::shared_ptr<Engine::ATexture> &texture)
{
    ASprite::setTexture(texture);
    _sprite.setTexture(*(std::dynamic_pointer_cast<TextureSFML>(texture)->getTexture()));
}

void SpriteSFML::setScale(Engine::Scale<float> scale)
{
    _sprite.setScale(scale.x, scale.y);
}

Engine::Scale<float> SpriteSFML::getScale() const
{
    return {_sprite.getScale().x, _sprite.getScale().y};
}

void SpriteSFML::setRect(Engine::Box<float> rect)
{
    _sprite.setTextureRect(sf::IntRect(rect.x1, rect.y1, rect.size.x, rect.size.y));
}

Engine::Box<float> SpriteSFML::getRect() const
{
    auto rect = _sprite.getTextureRect();

    return {static_cast<float>(rect.left), static_cast<float>(rect.top), static_cast<float>(rect.width), static_cast<float>(rect.height)};
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

void SpriteSFML::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<float> position, float angle)
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

Engine::Size<float> SpriteSFML::getSize() const
{
    return {_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height};
}