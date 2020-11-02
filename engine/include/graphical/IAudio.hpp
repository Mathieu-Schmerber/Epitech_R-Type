/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_IAUDIO_HPP
#define RTYPE_IAUDIO_HPP

#include <type_traits>
#include <iostream>

namespace Engine {

    class IAudio {
    public:
        IAudio() = default;
        virtual void loadFromFile(const std::string filename) = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void setVolume(float volume) = 0;
    };

}

#endif //RTYPE_IAUDIO_HPP
