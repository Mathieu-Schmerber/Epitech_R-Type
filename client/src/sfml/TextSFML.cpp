/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/TextSFML.hpp"

void TextSFML::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<float> position, float angle)
{
    std::shared_ptr<WindowSFML> windowSFML = std::dynamic_pointer_cast<WindowSFML>(window);

    setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    setRotation(angle);
    windowSFML->getWindow()->draw(_text);
}

void TextSFML::setRotation(float angle)
{
    _text.setRotation(angle);
}

void TextSFML::setPosition(Engine::Point<float> position)
{
    _text.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
}

Engine::Size<int> TextSFML::getSize() const
{
    return {static_cast<int>(_text.getGlobalBounds().width), static_cast<int>(_text.getGlobalBounds().height)};
}

void TextSFML::setCharacterSize(unsigned int size)
{
    return _text.setCharacterSize(size);
}

Engine::Point<float> TextSFML::getPosition() const
{
    return {_text.getPosition().x, _text.getPosition().y};
}

float TextSFML::getRotation() const
{
    return _text.getRotation();
}

void TextSFML::setString(const std::string text)
{
    _text.setString(text.data());
}

void TextSFML::setFont(std::shared_ptr<Engine::AFont> &font)
{
    AText::setFont(font);
    _text.setFont(std::dynamic_pointer_cast<FontSFML>(font)->getFont());
}

void TextSFML::setScale(Engine::Size<float> scale)
{
    _text.setScale(scale.x, scale.y);
}

void TextSFML::setOrigin(Engine::Point<float> origin)
{
    _text.setOrigin(origin.x, origin.y);
}

void TextSFML::setFillColor(Engine::Color color)
{
    _text.setFillColor(sf::Color({color.red, color.green, color.blue, color.alpha}));
}

void TextSFML::setOutlineColor(Engine::Color color)
{
    _text.setOutlineColor(sf::Color({color.red, color.green, color.blue, color.alpha}));
}

void TextSFML::setLetterSpacing(float spacingFactor)
{
    _text.setLetterSpacing(spacingFactor);
}

void TextSFML::setLineSpacing(float spacingFactor)
{
    _text.setLineSpacing(spacingFactor);
}

std::string TextSFML::toStdString() const
{
    return _text.getString().toAnsiString();
}
