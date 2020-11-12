//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_VELOCITYCOMPONENT_HPP
#define RTYPE_VELOCITYCOMPONENT_HPP

#include "tools/Geometry.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class VelocityComponent : public Engine::Component {
    private:
        Vector<float> _speed;
        Vector<float> _acceleration;

    public:
        explicit VelocityComponent(const Vector<float> &speed = {0, 0},
                                   const Vector<float> &acceleration = {0, 0})
                                   : _speed(speed), _acceleration(acceleration), Component() {}

        [[nodiscard]] Vector<float> getSpeed() const {return _speed;}
        [[nodiscard]] Vector<float> getAcceleration() const {return _acceleration;}
        void setSpeed(const Vector<float> &speed) {_speed = speed;}
        void setAcceleration(const Vector<float> &acceleration) {_acceleration = acceleration;}
    };

}

#endif //RTYPE_VELOCITYCOMPONENT_HPP