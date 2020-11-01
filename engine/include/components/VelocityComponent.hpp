//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_VELOCITYCOMPONENT_HPP
#define RTYPE_VELOCITYCOMPONENT_HPP

#include "ecs/Component.hpp"

namespace Engine {

    class VelocityComponent : Engine::Component {
    private:
        std::pair<double, double> _speed;
        std::pair<double, double> _acceleration;

    public:
        explicit VelocityComponent(const std::pair<double, double> &speed = {0, 0},
                                   const std::pair<double, double> &acceleration = {0, 0})
                                   : _speed(speed), _acceleration(acceleration), Component() {}

        const std::pair<double, double> getSpeed() const {return _speed;}
        const std::pair<double, double> getAcceleration() const {return _acceleration;}
        void setSpeed(const std::pair<double, double> &speed) {_speed = speed;}
        void setAcceleration(const std::pair<double, double> &acceleration) {_acceleration = acceleration;}
    };

}

#endif //RTYPE_VELOCITYCOMPONENT_HPP