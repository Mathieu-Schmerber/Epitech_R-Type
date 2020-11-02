//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_ASPRITE_HPP
#define RTYPE_ASPRITE_HPP

#include <utility>
#include <memory>
#include "tools/Geometry.hpp"
#include "AWindow.hpp"

namespace Engine {

    class ASprite {
    public:
        ASprite() = default;
        ~ASprite() = default;

        virtual Engine::Point<int> getSize() = 0;
        virtual void setScale(Engine::Scale<float> scale) = 0;
        virtual void setOrigin(Engine::Point<float> origin) = 0;
        virtual void setRect(Engine::Box<int> rect) = 0;
        virtual void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) = 0;
    };

}

#endif //RTYPE_ASPRITE_HPP