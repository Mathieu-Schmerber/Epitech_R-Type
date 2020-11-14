/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/TextSFML.hpp"

void TextSFML::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle)
{
    std::shared_ptr<WindowSFML> windowSFML = std::dynamic_pointer_cast<WindowSFML>(window);

    setPosition({static_cast<double>(position.x), static_cast<double>(position.y)});
    setRotation(angle);
    windowSFML->getWindow()->draw(_text);
}

void TextSFML::setRotation(double angle)
{
    _text.setRotation(static_cast<float>(angle));
}

void TextSFML::setPosition(Engine::Point<double> position)
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

Engine::Point<double> TextSFML::getPosition() const
{
    return {_text.getPosition().x, _text.getPosition().y};
}

double TextSFML::getRotation() const
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

void TextSFML::setScale(Engine::Size<double> scale)
{
    _text.setScale(static_cast<float>(scale.x), static_cast<float>(scale.y));
}

void TextSFML::setOrigin(Engine::Point<double> origin)
{
    _text.setOrigin(static_cast<float>(origin.x), static_cast<float>(origin.y));
}

void TextSFML::setFillColor(Engine::Color color)
{
    _text.setFillColor(sf::Color({color.red, color.green, color.blue, color.alpha}));
}

void TextSFML::setOutlineColor(Engine::Color color)
{
    _text.setOutlineColor(sf::Color({color.red, color.green, color.blue, color.alpha}));
}

void TextSFML::setLetterSpacing(double spacingFactor)
{
    _text.setLetterSpacing(static_cast<float>(spacingFactor));
}

void TextSFML::setLineSpacing(double spacingFactor)
{
    _text.setLineSpacing(static_cast<float>(spacingFactor));
}

std::string TextSFML::toStdString() const
{
    return _text.getString().toAnsiString();
}

int TextSFML::getCharacterSize() const
{
    return static_cast<int>(_text.getCharacterSize());
}

int TextSFML::getLetterSpacing() const
{
    return static_cast<int>(_text.getLetterSpacing());
}
