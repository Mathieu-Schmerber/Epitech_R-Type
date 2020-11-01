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
#include "enumerations/Key.hpp"
#include <iostream>

namespace Engine {

    class AEvents {
    public:
        AEvents() = default;
        virtual void update() = 0;

        virtual std::vector<Engine::Key> getKeysPressed() {return _pressed;};
        virtual std::vector<Engine::Key> getKeysReleased() {return _released;};


    protected:
        std::vector<Engine::Key> _pressed;
        std::vector<Engine::Key> _released;
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
