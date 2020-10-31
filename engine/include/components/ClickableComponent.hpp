//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CLICKABLECOMPONENT_HPP
#define RTYPE_CLICKABLECOMPONENT_HPP

#include "ecs/Component.hpp"

namespace Engine {

    class ClickableComponent : public Engine::Component {
    private:
        void (*_onclick)();

    public:
        explicit ClickableComponent(void (*onClick)() = nullptr) : _onclick(onClick), Component() {}

        void onClick() const {this->_onclick();}
        void setOnClick(void (*onClick)()) {this->_onclick = onClick;};
    };

}

#endif //RTYPE_CLICKABLECOMPONENT_HPP
