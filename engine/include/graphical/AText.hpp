/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ATEXT_HPP
#define RTYPE_ATEXT_HPP


#include "tools/Color.hpp"
#include "AFont.hpp"
#include "tools/Geometry.hpp"
#include "AWindow.hpp"
#include <iostream>
#include <memory>

namespace Engine {

    class AText {
    public:
        virtual void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) = 0;

        virtual void setFont(std::shared_ptr<Engine::AFont> &font);
        virtual void setScale(Engine::Size<double> scale) = 0;
        virtual void setOrigin(Engine::Point<double> origin) = 0;
        virtual void setFillColor(Engine::Color color) = 0;
        virtual void setOutlineColor(Engine::Color color) = 0;
        virtual void setString(std::string text) = 0;
        virtual void setRotation(double angle) = 0;
        virtual void setPosition(Engine::Point<double> position) = 0;
        virtual void setCharacterSize(unsigned int size) = 0;
        virtual void setLetterSpacing(double spacingFactor) = 0;
        virtual void setLineSpacing(double spacingFactor) = 0;
        [[nodiscard]] virtual Engine::Point<double> getPosition() const = 0;
        [[nodiscard]] virtual Engine::Size<int> getSize() const = 0;
        [[nodiscard]] virtual double getRotation() const = 0;
        [[nodiscard]] virtual std::shared_ptr<Engine::AFont> getFont() const;
        [[nodiscard]] virtual std::string toStdString() const = 0;
        [[nodiscard]] virtual int getCharacterSize() const = 0;
        [[nodiscard]] virtual int getLetterSpacing() const = 0;
        [[nodiscard]] virtual Engine::Color getFillColor() const = 0;

    protected:
        std::shared_ptr<Engine::AFont> _font;
    };
}


#endif //RTYPE_ATEXT_HPP
