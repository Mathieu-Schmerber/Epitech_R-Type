/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AEVENTS_HPP
#define RTYPE_AEVENTS_HPP

#include <iostream>
#include <algorithm>
#include "graphical/AWindow.hpp"
#include "enumerations/Inputs.hpp"
#include "tools/Geometry.hpp"

namespace Engine {

    class AEvents {
    public:
        AEvents() = default;
        virtual void update() = 0;

        virtual std::vector<Engine::Inputs> getKeysPressed() {return _keyPressed;};
        virtual std::vector<Engine::Inputs> getKeysReleased() {return _keyReleased;};

        virtual bool isButtonPressed(Engine::Mouse button) = 0;
        virtual std::vector<Engine::Mouse> getButtonsPressed() {return _buttonsPressed;};
        virtual std::vector<Engine::Mouse> getButtonsReleased() {return _buttonsReleased;};
        virtual Engine::Point<int> getMousePosWindowRelative() {return _mousePos;};
        virtual Engine::Point<int> getMousePosDesktopRelative() = 0;
        virtual bool isMouseInWindow() {return _mouseInWindow;};

        virtual Engine::Scroll getScrollState() {return _scroll;};

    protected:
        std::vector<Engine::Inputs> _keyPressed;
        std::vector<Engine::Inputs> _keyReleased;

        std::vector<Engine::Mouse> _buttonsPressed;
        std::vector<Engine::Mouse> _buttonsReleased;

        Engine::Scroll _scroll;
        Engine::Point<int> _mousePos;
        bool _mouseInWindow = true;
    };
}

#endif //RTYPE_AEVENTS_HPP
