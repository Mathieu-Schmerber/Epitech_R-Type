//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_CLICKABLECOMPONENT_HPP
#define RTYPE_CLICKABLECOMPONENT_HPP

#include "sceneManagement/AScene.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    /*!
     * @brief This component stores the mouse state relative to the entity it is attached to
     */
    class ClickableComponent : public Engine::Component {
    private:
        bool _isClicked;
        bool _isHover;
        bool _isReleased;

    public:
        ClickableComponent() : _isClicked(false), _isHover(false), _isReleased(false), Component() {}

        [[nodiscard]] bool isClicked() const {return this->_isClicked;}
        void setIsClicked(bool click) {this->_isClicked = click;}

        [[nodiscard]] bool isHover() const {return _isHover;}
        void setIsHover(bool isHover) {_isHover = isHover;}

        [[nodiscard]] bool isReleased() const {return _isReleased;}
        void setIsReleased(bool isReleased) {_isReleased = isReleased;}
    };

}

#endif //RTYPE_CLICKABLECOMPONENT_HPP
