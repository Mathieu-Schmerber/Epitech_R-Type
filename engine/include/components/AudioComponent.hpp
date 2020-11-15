/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AUDIOCOMPONENT_HPP
#define RTYPE_AUDIOCOMPONENT_HPP

#include "graphical/IAudio.hpp"
#include "ecs/Component.hpp"
#include <memory>

namespace Engine {

    class AudioComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::IAudio> _audio;

    public:
        explicit AudioComponent(std::unique_ptr<Engine::IAudio> audio = nullptr) : Engine::Component(), _audio(std::move(audio)) {}

        std::unique_ptr<Engine::IAudio> &getAudio() {return this->_audio;}
        void setAudio(std::unique_ptr<Engine::IAudio> audio) {this->_audio = std::move(audio);}
    };

}


#endif //RTYPE_AUDIOCOMPONENT_HPP
