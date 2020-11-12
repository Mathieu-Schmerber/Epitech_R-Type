//
// Created by mathi on 10/11/2020.
//

#include "ProjectileSystem.hpp"
#include "components/ProjectileComponent.hpp"

ProjectileSystem::ProjectileSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<ProjectileComponent>();
}

void ProjectileSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (e->getComponent<ProjectileComponent>()->isLifetimeOver())
            _game->despawn(e);
    }
}