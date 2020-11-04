/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "systems/MusicSystem.hpp"
#include "components/MusicComponent.hpp"

Engine::MusicSystem::MusicSystem()
{
    this->addDependency<Engine::MusicComponent>();
}

void Engine::MusicSystem::update()
{
    for (auto &e : this->_entities) {
        if (!e->getComponent<MusicComponent>()->getMusic()->isPlaying()
        && !e->getComponent<MusicComponent>()->getMusic()->isPaused())
            e->getComponent<MusicComponent>()->getMusic()->play();
    }
}
