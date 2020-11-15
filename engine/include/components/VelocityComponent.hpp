//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_VELOCITYCOMPONENT_HPP
#define RTYPE_VELOCITYCOMPONENT_HPP

#include "tools/Geometry.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    /*!
     * @brief This component stores all the data needed to move an Engine::Entity around
     */
    class VelocityComponent : public Engine::Component {
    private:
        Vector<double> _speed;
        Vector<double> _acceleration;

    public:
        explicit VelocityComponent(const Vector<double> &speed = {0, 0},
                                   const Vector<double> &acceleration = {0, 0})
                                   : _speed(speed), _acceleration(acceleration), Component() {}

        [[nodiscard]] Vector<double> getSpeed() const {return _speed;}
        [[nodiscard]] Vector<double> getAcceleration() const {return _acceleration;}
        void setSpeed(const Vector<double> &speed) {_speed = speed;}
        void setAcceleration(const Vector<double> &acceleration) {_acceleration = acceleration;}
    };

}

#endif //RTYPE_VELOCITYCOMPONENT_HPP