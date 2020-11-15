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

    /*!
     * @brief Describes a Music Entity
     */
    class Music : public Engine::Entity {
    public:
        explicit Music(std::unique_ptr<Engine::AMusic> music) : Engine::Entity()
        {
            this->addComponent<MusicComponent>(std::move(music));
        }
        ~Music() {
            getComponent<Engine::MusicComponent>()->getMusic()->close();
            _components.clear();
        }
    };
}

#endif //RTYPE_MUSIC_HPP