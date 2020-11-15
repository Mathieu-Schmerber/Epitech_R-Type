/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SOUNDCOMPONENT_HPP
#define RTYPE_SOUNDCOMPONENT_HPP

#include <graphical/ASound.hpp>
#include "ecs/Component.hpp"
#include <memory>

namespace Engine {

    /*!
     * @brief This component stores all the data needed to play a sound
     */
    class SoundComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::ASound> _sound;
        bool _playing;

    public:
        explicit SoundComponent(std::unique_ptr<Engine::ASound> sound = nullptr) : _playing(false), Engine::Component(), _sound(std::move(sound)) {}

        [[nodiscard]] std::unique_ptr<Engine::ASound> &getSound() {return this->_sound;}
        void setSound(std::unique_ptr<Engine::ASound> sound) { this->_sound = std::move(sound);}
        [[nodiscard]] bool wantsToBePlayed() const {return _playing;}
        void playMe(bool playing) {_playing = playing;}
    };

}

#endif //RTYPE_SOUNDCOMPONENT_HPP
