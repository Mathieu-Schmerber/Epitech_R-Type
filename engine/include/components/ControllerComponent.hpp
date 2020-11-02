//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CONTROLLERCOMPONENT_HPP
#define RTYPE_CONTROLLERCOMPONENT_HPP

#include <vector>
#include <algorithm>
#include "ecs/Component.hpp"
#include "enumerations/Inputs.hpp"

namespace Engine {

    class ControllerComponent : public Engine::Component {
    private:
        std::vector<Engine::Inputs> _pressed;
        std::vector<Engine::Inputs> _released;

    public:
        explicit ControllerComponent() : Engine::Component() {}

        void setPressed(const std::vector<Engine::Inputs> &list) {this->_pressed = list;}
        void setReleased(const std::vector<Engine::Inputs> &list) {this->_released = list;}
        std::vector<Engine::Inputs> getPressed() const {return this->_pressed;}
        std::vector<Engine::Inputs> getReleased() const {return this->_released;}
    };

}

#endif //RTYPE_CONTROLLERCOMPONENT_HPP