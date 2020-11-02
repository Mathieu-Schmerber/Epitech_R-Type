/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AMUSIC_HPP
#define RTYPE_AMUSIC_HPP

#include <iostream>

namespace Engine {

    class AMusic {
    public:
        AMusic() = default;
        virtual void loadFromFile(const std::string filename) = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void setVolume(float volume) = 0;

    protected:
        float _volume = 100;
    };

}

#endif //RTYPE_AMUSIC_HPP
