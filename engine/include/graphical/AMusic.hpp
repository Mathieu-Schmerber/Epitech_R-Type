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
        virtual void setVolume(float volume) override;

    protected:
        float _volume = 100;
    };

}

#endif //RTYPE_AMUSIC_HPP
