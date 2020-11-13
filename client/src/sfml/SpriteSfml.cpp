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

void SpriteSFML::setScale(Engine::Scale<double> scale)
{
    _sprite.setScale(static_cast<float>(scale.x), static_cast<float>(scale.y));
}

Engine::Scale<double> SpriteSFML::getScale() const
{
    return {_sprite.getScale().x, _sprite.getScale().y};
}

void SpriteSFML::setRect(Engine::Box<double> rect)
{
    _sprite.setTextureRect(sf::IntRect(static_cast<int>(rect.x1), static_cast<int>(rect.y1),
                                       static_cast<int>(rect.size.x), static_cast<int>(rect.size.y)));
}

Engine::Box<double> SpriteSFML::getRect() const
{
    auto rect = _sprite.getTextureRect();

    return {static_cast<double>(rect.left), static_cast<double>(rect.top), static_cast<double>(rect.width), static_cast<double>(rect.height)};
}

void SpriteSFML::setPosition(Engine::Point<double> position)
{
    _sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

Engine::Point<double> SpriteSFML::getPosition() const
{
    return {_sprite.getPosition().x, _sprite.getPosition().y};
}

void SpriteSFML::setOrigin(Engine::Point<double> origin)
{
    _sprite.setOrigin(static_cast<float>(origin.x), static_cast<float>(origin.y));
}

Engine::Point<double> SpriteSFML::getOrigin() const
{
    return {_sprite.getOrigin().x, _sprite.getOrigin().y};
}

void SpriteSFML::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle)
{
    std::shared_ptr<WindowSFML> windowSFML = std::dynamic_pointer_cast<WindowSFML>(window);

    setPosition({static_cast<double>(position.x), static_cast<double>(position.y)});
    setRotation(angle);
    windowSFML->getWindow()->draw(_sprite);
}

void SpriteSFML::setRotation(double angle)
{
    _sprite.setRotation(static_cast<float>(angle));
}

double SpriteSFML::getRotation()
{
    return _sprite.getRotation();
}

Engine::Size<double> SpriteSFML::getSize() const
{
    return {_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height};
}