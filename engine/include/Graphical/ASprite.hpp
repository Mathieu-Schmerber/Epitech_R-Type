//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_ASPRITE_HPP
#define RTYPE_ASPRITE_HPP

#include <utility>
#include "tools/Geometry.hpp"
#include "AWindow.hpp"
#include <memory>

namespace Engine {

    class ASprite {
    public:
        explicit ASprite() = default;
        ~ASprite() = default;

        virtual Engine::Point<int> getSize() = 0;
        virtual void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) = 0;
    };

}

#endif //RTYPE_ASPRITE_HPP