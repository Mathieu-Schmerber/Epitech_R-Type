//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CONTROLLERCOMPONENT_HPP
#define RTYPE_CONTROLLERCOMPONENT_HPP

#include <vector>
#include <algorithm>
#include "ecs/Component.hpp"
#include "enumerations/Key.hpp"

namespace Engine {

    class ControllerComponent : public Engine::Component {
    private:
        std::vector<Engine::Key> _pressed;
        std::vector<Engine::Key> _released;

        static void removeFrom(std::vector<Engine::Key> &list, Engine::Key input) {
            auto it = std::find(list.begin(), list.end(), input);

            if (it != list.end())
                list.erase(it);
        }

    public:
        explicit ControllerComponent() : Engine::Component() {}

        void press(Engine::Key input) {
            removeFrom(this->_pressed, input);
            removeFrom(this->_released, input);
            this->_pressed.push_back(input);
        }

        void releaseAll() {
            this->_released = this->_pressed;
            this->_pressed.clear();
        }

        std::vector<Engine::Key> getPressed() const {return this->_pressed;}
        std::vector<Engine::Key> getReleased() const {return this->_released;}
    };

}

#endif //RTYPE_CONTROLLERCOMPONENT_HPP