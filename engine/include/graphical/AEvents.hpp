/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AEVENTS_HPP
#define RTYPE_AEVENTS_HPP

#include <algorithm>
#include "graphical/AWindow.hpp"
#include "enumerations/Inputs.hpp"
#include <iostream>
#include <tools/Geometry.hpp>

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
        virtual Engine::Point<int> getMousePos() {return _mousePos;};
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

template<typename T>
void removeInVector(std::vector<T> &vector, T item)
{
    vector.erase(std::remove_if(vector.begin(), vector.end(), [item](T x){return x == item;}));
}

template<typename T>
bool isInVector(std::vector<T> &vector, T item)
{
    return (std::find_if(vector.begin(), vector.end(), [item](T x){return x == item;}) != vector.end());
}

#endif //RTYPE_AEVENTS_HPP
