//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_PARALLAXCOMPONENT_HPP
#define RTYPE_PARALLAXCOMPONENT_HPP

#include "tools/Geometry.hpp"
#include "tools/Utils.hpp"
#include "graphical/ASprite.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class ParallaxComponent : public Engine::Component {
    private:
        Point<int> _start;
        Point<int> _limit;

    public:
        explicit ParallaxComponent() : _start({0, 0}), _limit({0, 0}), Engine::Component() {}
        explicit ParallaxComponent(const Point<int> &start, const Point<int> &limit) : _start(start), _limit(limit),
        Engine::Component() {}

        [[nodiscard]] bool isLimitReached(const Point<int> &pos, const Vector<double> &direction) const {
            return (
                    (direction.x >= 0 && pos.x >= _limit.x) && (direction.y >= 0 && pos.y >= _limit.y) ||
                    (direction.x <= 0 && pos.x <= _limit.x) && (direction.y <= 0 && pos.y <= _limit.y)
            );
        }

        [[nodiscard]] Point<int> getStart() const {return this->_start;}
        [[nodiscard]] Point<int> getLimit() const {return this->_limit;}
        void setStart(const Point<int> &start) {this->_start = start;}
        void setLimit(const Point<int> &limit) {this->_limit = limit;}
    };

}

#endif //RTYPE_PARALLAXCOMPONENT_HPP
