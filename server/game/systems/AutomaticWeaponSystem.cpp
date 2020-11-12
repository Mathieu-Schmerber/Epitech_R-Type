/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "entities/Projectile.hpp"
#include "components/AutomaticWeaponComponent.hpp"
#include "AutomaticWeaponSystem.hpp"

AutomaticWeaponSystem::AutomaticWeaponSystem(std::shared_ptr<Game> &game) : _game(game)
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<AutomaticWeaponComponent>();
    this->_projectileTexture = std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_1_72x18_18x18.png");
}

bool AutomaticWeaponSystem::hasToShoot(AutomaticWeaponComponent *weapon)
{
    return false; // FIXME selon le pattern
}

void AutomaticWeaponSystem::automaticShot(std::shared_ptr<Engine::Entity> &shooter)
{
    auto weapon = shooter->getComponent<AutomaticWeaponComponent>();
    auto transform = shooter->getComponent<Engine::TransformComponent>();

    if (hasToShoot(weapon) && weapon->canShoot()) {
        weapon->refreshShoots();
        std::shared_ptr<Engine::Entity> projectile = std::make_shared<Projectile>(
                transform->getPos(), Engine::Point<int>{18, 18}, Engine::Vector<double>{3, 0},
                weapon->getCurrentDamages(), 2, this->_projectileTexture); // FIXME changer le collision masque
        this->_game->spawn(projectile, true);
    }
}

void AutomaticWeaponSystem::update()
{
    for (auto &e : this->_entities) {
        automaticShot(e);
    }
}
