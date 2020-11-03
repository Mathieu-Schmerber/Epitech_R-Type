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
        void setVolume(float volume) override;
        virtual bool isPlaying() const = 0;
        virtual bool isPaused() const = 0;
        virtual bool isStopped() const = 0;
        virtual void setLoop(bool loop=true) = 0;
        virtual bool isLooping() const = 0;

    protected:
        float _volume = 100;
    };

}

#endif //RTYPE_AMUSIC_HPP