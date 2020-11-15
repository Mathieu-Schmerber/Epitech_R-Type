//
// Created by mathi on 15/11/2020.
//

#include "systems/MusicSystem.hpp"
#include "components/MusicComponent.hpp"

Engine::MusicSystem::MusicSystem(std::shared_ptr<AWindow> &window) : _window(window), Engine::System()
{
    this->addDependency<MusicComponent>();
}

void Engine::MusicSystem::deleteEntity(std::shared_ptr<Engine::Entity> &entity)
{
    auto music = entity->getComponent<Engine::MusicComponent>();

    if (music)
        music->getMusic()->stop();
    Engine::Utils::removeFromVector(this->_entities, entity);
}

void Engine::MusicSystem::update()
{
    MusicComponent *music;

    if (!_window->hasMusic())
        return;
    for (auto &e : this->_entities) {
        music = e->getComponent<MusicComponent>();
        if (music->wantsToBePlayed() && !music->getMusic()->isPlaying()) {
            music->getMusic()->play(100);
            music->playMe(false);
        } else if (music->wantsToBeStoped() && !music->getMusic()->isStopped()) {
            music->getMusic()->stop();
            music->stopMe(false);
        }
    }
}