/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ASOUND_HPP
#define RTYPE_ASOUND_HPP

#include <iostream>

namespace Engine {

    class ASound {
    public:
        ASound() = default;
        virtual void loadFromFile(const std::string filename) = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void setVolume(float volume) = 0;

    protected:
        float _volume = 100;
    };

}

#endif //RTYPE_ASOUND_HPP
