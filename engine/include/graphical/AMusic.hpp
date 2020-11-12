/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AMUSIC_HPP
#define RTYPE_AMUSIC_HPP

#include <iostream>
#include "IAudio.hpp"

namespace Engine {

    class AMusic : public Engine::IAudio {
    public:
        AMusic() = default;
        void setVolume(double volume) override;
        virtual bool isPlaying() const = 0;
        virtual bool isPaused() const = 0;
        virtual bool isStopped() const = 0;
        virtual void setLoop(bool loop=true) = 0;
        virtual bool isLooping() const = 0;
        virtual void close() = 0;

    protected:
        double _volume = 0;
    };
}

#endif //RTYPE_AMUSIC_HPP
