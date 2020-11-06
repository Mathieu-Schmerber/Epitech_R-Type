/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_MusicCOMPONENT_HPP
#define RTYPE_MusicCOMPONENT_HPP

#include <graphical/AMusic.hpp>
#include "ecs/Component.hpp"
#include <memory>

namespace Engine {

class MusicComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::AMusic> _music;

    public:
        explicit MusicComponent(std::unique_ptr<Engine::AMusic> music = nullptr) : Engine::Component(), _music(std::move(music)) {}

    [[nodiscard]] std::unique_ptr<Engine::AMusic> &getMusic() {return this->_music;}
        void setMusic(std::unique_ptr<Engine::AMusic> music) { this->_music = std::move(music);}
    };

}

#endif //RTYPE_MusicCOMPONENT_HPP
