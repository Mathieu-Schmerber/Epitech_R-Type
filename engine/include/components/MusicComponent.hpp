/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_MusicCOMPONENT_HPP
#define RTYPE_MusicCOMPONENT_HPP

#include <memory>
#include "graphical/AMusic.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class MusicComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::AMusic> _music;
        bool _playing;

    public:
        explicit MusicComponent(std::unique_ptr<Engine::AMusic> music = nullptr) : _playing(false), Engine::Component(),
                                                                                   _music(std::move(music)) {}

        [[nodiscard]] std::unique_ptr<Engine::AMusic> &getMusic() { return this->_music; }

        void setMusic(std::unique_ptr<Engine::AMusic> music) { this->_music = std::move(music); };

        [[nodiscard]] bool wantsToBePlayed() const { return _playing; }

        void playMe(bool playing) { _playing = playing; }
    };
}

#endif //RTYPE_MusicCOMPONENT_HPP
