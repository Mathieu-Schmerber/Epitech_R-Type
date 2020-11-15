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

    public:
        TextSFML(const std::string &text, std::shared_ptr<Engine::AFont> &font, unsigned int characterSize) : Engine::AText() {
            setString(text);
            setFont(font);
            setCharacterSize(characterSize);
        }
        void setFont(std::shared_ptr<Engine::AFont> &font) final;
        void setScale(Engine::Size<double> scale) final;
        void setOrigin(Engine::Point<double> origin) final;
        void setFillColor(Engine::Color color) final;
        void setOutlineColor(Engine::Color color) final;
        void setString(std::string text) final;
        void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) final;
        void setRotation(double angle) final;
        void setPosition(Engine::Point<double> position) final;
        void setCharacterSize(unsigned int size) final;
        void setLetterSpacing(double spacingFactor) final;
        void setLineSpacing(double spacingFactor) final;
        [[nodiscard]] Engine::Point<double> getPosition() const final;
        [[nodiscard]] Engine::Size<int> getSize() const final;
        [[nodiscard]] double getRotation() const final;
        [[nodiscard]] std::string toStdString() const final;
        [[nodiscard]] int getCharacterSize() const final;
        [[nodiscard]] int getLetterSpacing() const final;
        [[nodiscard]] Engine::Color getFillColor() const final;

};


#endif //RTYPE_TEXTSFML_HPP
