/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ASOUND_HPP
#define RTYPE_ASOUND_HPP

#include <iostream>
#include "IAudio.hpp"

namespace Engine {

    class ASound : public Engine::IAudio {
    public:
        ASound() = default;
        virtual void setVolume(float volume) override;

    protected:
        float _volume = 100;
    };

}

#endif //RTYPE_ASOUND_HPP
