//
// Created by mathi on 09/11/2020.
//

#ifndef RTYPE_BUTTONCOMPONENT_HPP
#define RTYPE_BUTTONCOMPONENT_HPP

#include "sceneManagement/AScene.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class ButtonComponent : public Engine::Component {
    private:
        void (*_onclick)(std::shared_ptr<Engine::AScene> &);
        std::shared_ptr<Engine::AScene> _arg;

    public:
        enum ButtonState {
            IDLE,
            HOVER,
            CLICKED
        };

        ButtonComponent() : _onclick(nullptr), Component() {}

        ButtonComponent(void (*onClick)(std::shared_ptr<Engine::AScene> &),
                           std::shared_ptr<Engine::AScene> &arg)
                : _onclick(onClick), _arg(arg), Component() {}

        void onClick() {
            (*_onclick)(_arg);
        }

        void setOnClick(void (*onClick)(std::shared_ptr<Engine::AScene> &)) {this->_onclick = onClick;};
        void setArg(std::shared_ptr<Engine::AScene> &arg) {this->_arg = arg;}
    };

}

#endif //RTYPE_BUTTONCOMPONENT_HPP
