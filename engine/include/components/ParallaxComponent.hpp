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

    /*!
     * @brief This component stores all the data needed to create a parallax effect
     */
    class ParallaxComponent : public Engine::Component {
    private:
        Point<double> _start;
        Point<double> _limit;
        bool _isAutomatic;

    public:
        explicit ParallaxComponent() : _start({0, 0}), _limit({0, 0}), _isAutomatic(true), Engine::Component() {}
        explicit ParallaxComponent(const Point<double> &start, const Point<double> &limit, bool automatic = true) : _isAutomatic(automatic), _start(start), _limit(limit),

        Engine::Component() {}

        /*!
         * @brief Check if the parallax needs to reset its position.
         * @param pos Current position
         * @param direction Parallax direction
         * @return True if the parallax needs to reset its position
         */
        [[nodiscard]] bool isLimitReached(const Point<double> &pos, const Vector<double> &direction) const {
            return (
                    (direction.x >= 0 && pos.x >= _limit.x) && (direction.y >= 0 && pos.y >= _limit.y) ||
                    (direction.x <= 0 && pos.x <= _limit.x) && (direction.y <= 0 && pos.y <= _limit.y)
            );
        }

        /*!
         * @brief Does the parallax reset its position automatically
         */
        [[nodiscard]] bool isAutomatic() const {return _isAutomatic;}
		
        [[nodiscard]] Point<double> getStart() const {return this->_start;}
        [[nodiscard]] Point<double> getLimit() const {return this->_limit;}
        void setStart(const Point<double> &start) {this->_start = start;}
        void setLimit(const Point<double> &limit) {this->_limit = limit;}
    };

}

#endif //RTYPE_PARALLAXCOMPONENT_HPP
