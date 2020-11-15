/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "components/HealthComponent.hpp"
#include "components/ChildrenComponent.hpp"
#include "HealthSystem.hpp"

HealthSystem::HealthSystem(std::shared_ptr<Game> &game) : _game(game)
{
    addDependency<HealthComponent>();
}

void HealthSystem::update()
{
    std::vector<std::shared_ptr<Engine::Entity>> tmp = _entities;
    std::vector<std::shared_ptr<Engine::Entity>> child;
    Engine::ChildrenComponent *children = nullptr;

    for (auto &e : tmp) {
        children = e->getComponent<Engine::ChildrenComponent>();
        if (e->getComponent<HealthComponent>()->getCurrentHealth() <= 0) {
            if (e->getComponent<Engine::SpriteComponent>() && e->getComponent<Engine::SpriteComponent>()->getSprite()->getTexture()->getFilename() == "../../client/assets/images/starships/blue_starship_166x17_33x17.png")
                std::cout << "player dispawn health" << std::endl;
            _game->despawn(e);
            if (children) {
                child = children->getChildren();
                for (auto &c : child)
                    _game->despawn(c);
            }
        }
    }
}
