/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TEXTSFML_HPP
#define RTYPE_TEXTSFML_HPP

#include <SFML/Graphics/Text.hpp>
#include "graphical/AText.hpp"
#include "graphical/AFont.hpp"
#include "graphical/AWindow.hpp"
#include "tools/Geometry.hpp"
#include "sfml/FontSFML.hpp"
#include "sfml/WindowSFML.hpp"
#include <iostream>
#include <memory>

class TextSFML : public Engine::AText {
private:
    sf::Text _text;
    sf::String _string;

public:
    TextSFML(const std::string text, std::shared_ptr<Engine::AFont> &font, unsigned int characterSize) : Engine::AText() {
        setString(text);
        setFont(font);
        setCharacterSize(characterSize);
    }
    void setFont(std::shared_ptr<Engine::AFont> &font) final;
    void setScale(Engine::Size<float> scale) final;
    void setOrigin(Engine::Point<float> origin) final;
    void setFillColor(Engine::Color color) final;
    void setOutlineColor(Engine::Color color) final;
    void setString(std::string text) final;
    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) final;
    void setRotation(float angle) final;
    void setPosition(Engine::Point<float> position) final;
    void setCharacterSize(unsigned int size) final;
    void setLetterSpacing(float spacingFactor) final;
    void setLineSpacing(float spacingFactor) final;
    [[nodiscard]] Engine::Point<float> getPosition() const final;
    [[nodiscard]] Engine::Size<int> getSize() const final;
    [[nodiscard]] float getRotation() const final;
};


#endif //RTYPE_TEXTSFML_HPP
