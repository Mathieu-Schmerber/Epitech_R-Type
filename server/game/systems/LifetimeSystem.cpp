//
// Created by mathi on 13/11/2020.
//

#include "LifetimeSystem.hpp"
#include "components/LifetimeComponent.hpp"

LifetimeSystem::LifetimeSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<LifetimeComponent>();
}

void LifetimeSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (e->getComponent<LifetimeComponent>()->isLifetimeOver())
            _game->despawn(e);
    }
}