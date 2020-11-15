//
// Created by mathi on 09/11/2020.
//

#ifndef RTYPE_BUTTONCOMPONENT_HPP
#define RTYPE_BUTTONCOMPONENT_HPP

#include "sceneManagement/AScene.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    /*!
     * @brief This component stores all the data needed to create a button
     */
    class ButtonComponent : public Engine::Component {
    private:
        void (*_onclick)(std::shared_ptr<Engine::AScene> &);
        std::shared_ptr<Engine::AScene> _arg;

    public:
        /*!
        * @brief Button animation state
        */
        enum ButtonState {
            IDLE,
            HOVER,
            CLICKED
        };

        ButtonComponent() : _onclick(nullptr), Component() {}

        /*!
         * @brief Create a button component.
         * @param onClick button callback function
         * @param arg button callback argument
         */
        ButtonComponent(void (*onClick)(std::shared_ptr<Engine::AScene> &),
                           std::shared_ptr<Engine::AScene> &arg)
                : _onclick(onClick), _arg(arg), Component() {}

        /*!
         * @brief Call the button's callback function
         */
        void onClick() {
            (*_onclick)(_arg);
        }

        void setOnClick(void (*onClick)(std::shared_ptr<Engine::AScene> &)) {this->_onclick = onClick;};
        void setArg(std::shared_ptr<Engine::AScene> &arg) {this->_arg = arg;}
    };

}

#endif //RTYPE_BUTTONCOMPONENT_HPP
