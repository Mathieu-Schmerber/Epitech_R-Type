//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_TRANSFORMCOMPONENT_HPP
#define RTYPE_TRANSFORMCOMPONENT_HPP

#include <utility>
#include <cmath>
#include "ecs/Component.hpp"

namespace Engine {

    class TransformComponent : public Engine::Component {
    private:
        std::pair<int, int> _pos;
        double _rotation;
        std::pair<double, double> _normal;

    public:
        explicit TransformComponent(const std::pair<int, int> &pos,
                                    double rotation,
                                    const std::pair<double, double> &normal)
                : _pos(pos), _rotation(rotation), _normal(normal), Component() {}

        std::pair<int, int> getPos() const { return this->_pos; }
        void setPos(const std::pair<int, int> &pos) {this->_pos = pos;}

        double getRotation() const {return this->_rotation;}
        void setRotation(double rotation) {this->_rotation = rotation;}

        std::pair<double, double> getNormal() const
        {
            const double PI = 3.141592653589793238463;
            double angle = this->_rotation * (PI / 180);
            std::pair<double, double> res = {
                    _normal.first * cos(angle) - _normal.second * sin(angle),
                    _normal.first * sin(angle) + _normal.second * cos(angle)};

            return res;
        }

    };

}

#endif //RTYPE_TRANSFORMCOMPONENT_HPP