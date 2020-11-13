//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_ASPRITE_HPP
#define RTYPE_ASPRITE_HPP

#include <utility>
#include <memory>
#include "tools/Geometry.hpp"
#include "AWindow.hpp"
#include "ATexture.hpp"

namespace Engine {

    class ASprite {
    public:
        ASprite() = default;
        ~ASprite() = default;

        [[nodiscard]] virtual Engine::Point<double> getSize() const = 0;
        [[nodiscard]] virtual Engine::Box<double> getRect() const = 0;
        virtual void setTexture(std::shared_ptr<Engine::ATexture> &texture);
        virtual void setScale(Engine::Scale<double> scale) = 0;
        virtual void setOrigin(Engine::Point<double> origin) = 0;
        [[nodiscard]] virtual Engine::Point<double> getOrigin() const = 0;
        [[nodiscard]] virtual Engine::Point<double> getPosition() const = 0;
        virtual void setRect(Engine::Box<double> rect) = 0;
        virtual void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) = 0;
        [[nodiscard]] std::shared_ptr<Engine::ATexture> &getTexture() {return _texture;}

    protected:
        std::shared_ptr<Engine::ATexture> _texture;
    };

}

#endif //RTYPE_ASPRITE_HPP