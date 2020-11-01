//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CONTROLLERCOMPONENT_HPP
#define RTYPE_CONTROLLERCOMPONENT_HPP

#include <vector>
#include <algorithm>
#include "ecs/Component.hpp"
#include "enumerations/Input.hpp"

namespace Engine {

    class ControllerComponent : public Engine::Component {
    private:
        std::vector<Engine::Input> _pressed;
        std::vector<Engine::Input> _released;

        static void removeFrom(std::vector<Engine::Input> &list, Engine::Input input) {
            auto it = std::find(list.begin(), list.end(), input);

            if (it != list.end())
                list.erase(it);
        }

    public:
        explicit ControllerComponent() : Engine::Component() {}

        void press(Engine::Input input) {
            removeFrom(this->_pressed, input);
            removeFrom(this->_released, input);
            this->_pressed.push_back(input);
        }

        void releaseAll() {
            this->_released = this->_pressed;
            this->_pressed.clear();
        }

        std::vector<Engine::Input> getPressed() const {return this->_pressed;}
        std::vector<Engine::Input> getReleased() const {return this->_released;}
    };

}

#endif //RTYPE_CONTROLLERCOMPONENT_HPP