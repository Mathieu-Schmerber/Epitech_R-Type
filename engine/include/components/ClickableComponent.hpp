//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CLICKABLECOMPONENT_HPP
#define RTYPE_CLICKABLECOMPONENT_HPP

#include "sceneManagement/AScene.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class ClickableComponent : public Engine::Component {
    private:
        void (*_onclick)(std::shared_ptr<Engine::AScene> &);
        std::shared_ptr<Engine::AScene> _arg;

    public:
        ClickableComponent() : _onclick(nullptr), Component() {}

        ClickableComponent(void (*onClick)(std::shared_ptr<Engine::AScene> &),
                           std::shared_ptr<Engine::AScene> &arg)
                           : _onclick(onClick), _arg(arg), Component() {}

        void onClick() {
            (*_onclick)(_arg);
        }

        void setOnClick(void (*onClick)(std::shared_ptr<Engine::AScene> &)) {this->_onclick = onClick;};
        void setArg(std::shared_ptr<Engine::AScene> &arg) {this->_arg = arg;}
    };

}

#endif //RTYPE_CLICKABLECOMPONENT_HPP
