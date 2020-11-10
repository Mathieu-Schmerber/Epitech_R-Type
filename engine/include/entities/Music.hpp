/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_MUSIC_HPP
#define RTYPE_MUSIC_HPP

#include "components/MusicComponent.hpp"
#include "ecs/Entity.hpp"

namespace Engine {

    class Music : public Engine::Entity {
    public:
        explicit Music(std::unique_ptr<Engine::AMusic> music) : Engine::Entity()
        {
            this->addComponent<MusicComponent>(std::move(music));
        }
    };
}

#endif //RTYPE_MUSIC_HPP
