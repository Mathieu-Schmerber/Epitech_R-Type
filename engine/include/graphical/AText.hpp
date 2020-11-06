/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ATEXT_HPP
#define RTYPE_ATEXT_HPP

#include <iostream>
#include "tools/Color.hpp"
#include "AFont.hpp"
#include <memory>
#include <tools/Geometry.hpp>
#include "AWindow.hpp"

namespace Engine {

    class AText {
    public:
        virtual void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) = 0;

        virtual void setFont(std::shared_ptr<Engine::AFont> &font);
        virtual void setScale(Engine::Size<float> scale) = 0;
        virtual void setOrigin(Engine::Point<float> origin) = 0;
        virtual void setFillColor(Engine::Color color) = 0;
        virtual void setOutlineColor(Engine::Color color) = 0;
        virtual void setString(std::string text) = 0;
        virtual void setRotation(float angle) = 0;
        virtual void setPosition(Engine::Point<float> position) = 0;
        virtual void setCharacterSize(unsigned int size) = 0;
        virtual void setLetterSpacing(float spacingFactor) = 0;
        virtual void setLineSpacing(float spacingFactor) = 0;
        [[nodiscard]] virtual Engine::Point<float> getPosition() const = 0;
        [[nodiscard]] virtual Engine::Size<int> getSize() const = 0;
        [[nodiscard]] virtual float getRotation() const = 0;
        [[nodiscard]] virtual std::shared_ptr<Engine::AFont> getFont() const;

    protected:
        std::shared_ptr<Engine::AFont> _font;
    };
}


#endif //RTYPE_ATEXT_HPP
