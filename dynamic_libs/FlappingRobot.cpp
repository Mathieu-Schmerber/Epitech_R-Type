/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "entities/Ground.hpp"
#include "CollisionMasks.hpp"
#include "components/ProjectileComponent.hpp"
#include "FlappingRobot.hpp"
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
        return new FlappingRobot();
    }
}

void pattern(std::shared_ptr<Engine::Entity> &enemy)
{
    auto velocity = enemy->getComponent<Engine::VelocityComponent>();

    if (enemy->getComponent<Engine::TransformComponent>()->getPos().y >= (GROUND_HEIGHT * 5) && Engine::RandomETU::randETU<double>(0, 30) == Engine::RandomETU::randETU<double>(0, 30)) {
        velocity->setSpeed(Engine::Vector<double>({velocity->getSpeed().x, -30}));
    }
    if (enemy->getComponent<Engine::TransformComponent>()->getPos().y >= (1080 - (GROUND_HEIGHT * 4))) {
        velocity->setSpeed(Engine::Vector<double>({velocity->getSpeed().x, -30}));
    }
}

FlappingRobot::FlappingRobot(const Engine::Point<double> &pos) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<double>{pos, {SIZE_X, SIZE_Y}})), pos)
{
        this->addComponent<PatternComponent>(&pattern);
        this->addComponent<AutomaticWeaponComponent>(1, 1,Engine::Vector<double>{-100, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::BASIC);
        this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<double>>>{
                {DEFAULT, {
                                  {_size.x * 0, _size.x * 1, 0, _size.y},
                                  {_size.x * 1, _size.x * 2, 0, _size.y},
                                  {_size.x * 2, _size.x * 3, 0, _size.y},
                                  {_size.x * 3, _size.x * 4, 0, _size.y},
                                  {_size.x * 4, _size.x * 5, 0, _size.y},
                                  {_size.x * 5, _size.x * 6, 0, _size.y},
                                  {_size.x * 6, _size.x * 7, 0, _size.y},
                                  {_size.x * 7, _size.x * 8, 0, _size.y}}}
        }, true);
    this->addComponent<HealthComponent>(2);
    this->addComponent<Engine::ColliderComponent>(Collision::ENEMY, pos, _size);
    this->addComponent<Engine::VelocityComponent>(Engine::Vector<double>({-13, -30}), Engine::Vector<double>({0, 1}));
}