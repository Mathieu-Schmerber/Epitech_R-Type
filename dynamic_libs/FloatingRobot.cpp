/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "entities/Ground.hpp"
#include "CollisionMasks.hpp"
#include "components/ProjectileComponent.hpp"
#include "FloatingRobot.hpp"
#include "tools/Geometry.hpp"

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
        return new FloatingRobot();
    }
}

void pattern(std::shared_ptr<Engine::Entity> &enemy)
{
    auto velocity = enemy->getComponent<Engine::VelocityComponent>();

    if (velocity->getSpeed().x < -15)
        velocity->setAcceleration({-0.03, 0});

    if (enemy->getComponent<Engine::TransformComponent>()->getPos().y >= 1080 - (GROUND_HEIGHT * 4) ||
            enemy->getComponent<Engine::TransformComponent>()->getPos().y <= (GROUND_HEIGHT * 4)) {
        auto speed = enemy->getComponent<Engine::VelocityComponent>()->getSpeed() * Engine::Vector<double>({1, -1});
        enemy->getComponent<Engine::VelocityComponent>()->setSpeed(speed);
    }
}

FloatingRobot::FloatingRobot(const Engine::Point<double> &pos) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<double>{pos, {SIZE_X, SIZE_Y}})), pos)
{
        this->addComponent<PatternComponent>(&pattern);
        this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-100, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::BASIC);
        this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<double>>>{
                {DEFAULT, {
                                  {_size.x * 0, _size.x * 1, 0, _size.y},
                                  {_size.x * 1, _size.x * 2, 0, _size.y},
                                  {_size.x * 2, _size.x * 3, 0, _size.y}}}
        }, true);
    this->addComponent<HealthComponent>(3);
    this->addComponent<Engine::ColliderComponent>(Collision::ENEMY, pos, _size);
    this->addComponent<Engine::VelocityComponent>(Engine::Vector<double>({0, -10}), Engine::Vector<double>({-0.7, 0}));
}