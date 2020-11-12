/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include <dataHolders/DataTexture.hpp>
#include <components/WeaponComponent.hpp>
#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<WeaponComponent>();
    this->_projectileTexture = std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_1_72x18_18x18.png");
}

void EnemySystem::update()
{
    for (auto &e : this->_entities) {
        std::cout << "update enemy" << std::endl;
    }
}
