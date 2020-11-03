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

    class SoundComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::ASound> _sound;

    public:
        explicit SoundComponent(std::unique_ptr<Engine::ASound> sound = nullptr) : Engine::Component(), _sound(std::move(sound)) {}

        std::unique_ptr<Engine::ASound> &getSound() {return this->_sound;}
        void setSound(std::unique_ptr<Engine::ASound> sound) { this->_sound = std::move(sound);}
    };

}

#endif //RTYPE_SOUNDCOMPONENT_HPP
