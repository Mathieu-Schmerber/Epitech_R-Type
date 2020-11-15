//
// Created by mathi on 15/11/2020.
//

#include "systems/SoundSystem.hpp"
#include "components/SoundComponent.hpp"

Engine::SoundSystem::SoundSystem() : Engine::System()
{
    this->addDependency<SoundComponent>();
}

void Engine::SoundSystem::update()
{
    SoundComponent *sound;

    for (auto &e : this->_entities) {
        sound = e->getComponent<SoundComponent>();
        if (sound->wantsToBePlayed() && !sound->getSound()->isPlaying())
            sound->getSound()->play(100);
    }
}