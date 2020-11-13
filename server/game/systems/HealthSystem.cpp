/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "components/HealthComponent.hpp"
#include "HealthSystem.hpp"

HealthSystem::HealthSystem(std::shared_ptr<Game> &game)  : _game(game)
{
    addDependency<HealthComponent>();
}

void HealthSystem::update()
{
    std::vector<std::shared_ptr<Engine::Entity>> tmp = _entities;

    for (auto &e : tmp) {
        if (e->getComponent<HealthComponent>()->getCurrentHealth() <= 0)
            _game->despawn(e);
    }
}
