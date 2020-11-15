//
// Created by mathi on 15/11/2020.
//

#include "systems/MusicSystem.hpp"
#include "components/MusicComponent.hpp"

Engine::MusicSystem::MusicSystem() : Engine::System()
{
    this->addDependency<MusicComponent>();
}

void Engine::MusicSystem::update()
{
    MusicComponent *music;

    for (auto &e : this->_entities) {
        music = e->getComponent<MusicComponent>();
        if (music->wantsToBePlayed() && !music->getMusic()->isPlaying())
            music->getMusic()->play(100);
    }
}