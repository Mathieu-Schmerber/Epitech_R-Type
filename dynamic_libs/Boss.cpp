/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "entities/Ground.hpp"
#include "CollisionMasks.hpp"
#include "components/ProjectileComponent.hpp"
#include "Boss.hpp"
#include "tools/Geometry.hpp"
#include "GameData.hpp"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
    #include <stdio.h>
#endif

extern "C" {
#if defined(_WIN32) || defined(WIN32)
__declspec(dllexport)
#endif
Enemy* newInstance()
{
    return new Boss();
}
}

void pattern(std::shared_ptr<Engine::Entity> &enemy)
{
    auto velocity = enemy->getComponent<Engine::VelocityComponent>();
    auto transform = enemy->getComponent<Engine::TransformComponent>();
    auto animation = enemy->getComponent<Engine::AnimationComponent>();

    if (transform->getPos().x < 1600)
        velocity->setAcceleration(Engine::Vector<double>({1, 0}));

    if (velocity->getSpeed().x >= 0) {
        velocity->setSpeed(Engine::Vector<double>({0, 0}));
        velocity->setAcceleration(Engine::Vector<double>({0, 0}));
    }
    if (enemy->getComponent<Engine::TransformComponent>()->getPos().y >= (GROUND_HEIGHT * 4) || enemy->getComponent<Engine::TransformComponent>()->getPos().y >= 1080 - SIZE_Y - (GROUND_HEIGHT * 2)) {
        velocity->setSpeed(Engine::Vector<double>(velocity->getSpeed() * Engine::Vector<double>({1, -1})));
    }
}

Boss::Boss(const Engine::Point<double> &pos) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<double>{pos, {SIZE_X, SIZE_Y}})), pos)
{
    this->addComponent<PatternComponent>(&pattern);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-40, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::BASIC);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-10, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::BEAM);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-20, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::SHURIKEN);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-20, -20}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::SHURIKEN);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-20, 20}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::SHURIKEN);
    this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<double>>>{
            {DEFAULT, {
                              {_size.x * 0, _size.x * 1, 0, _size.y},
                              {_size.x * 1, _size.x * 2, 0, _size.y}}}
    }, true);
    this->addComponent<HealthComponent>(2);
    this->addComponent<Engine::ColliderComponent>(Collision::ENEMY, pos, _size);
    this->addComponent<Engine::VelocityComponent>(Engine::Vector<double>({-10 + FLOOR_SPEED, -5}), Engine::Vector<double>({0, 0}));
    this->addComponent<Engine::TargetComponent>();
}