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
        [[nodiscard]] virtual bool isPlaying() const {return false;};
        [[nodiscard]] virtual bool isPaused() const {return false;};
        [[nodiscard]] virtual bool isStopped() const {return false;};
        virtual void setLoop(bool loop) {};
        [[nodiscard]] virtual bool isLooping() const {return false;};
        virtual void close() = 0;
        [[nodiscard]] std::string getFile() const {return this->_file;}

    protected:
        double _volume = 0;
        std::string _file;
    };
}

#endif //RTYPE_AMUSIC_HPP
