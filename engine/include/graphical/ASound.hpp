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
        void setVolume(double volume) override;
        [[nodiscard]] virtual bool isPlaying() const {return false;};
        [[nodiscard]] std::string getFile() const {return this->_file;}

    protected:
        double _volume = 100;
        std::string _file;
    };

}

#endif //RTYPE_ASOUND_HPP
