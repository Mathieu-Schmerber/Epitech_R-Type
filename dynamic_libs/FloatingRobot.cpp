/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "CollisionMasks.hpp"
#include "FloatingRobot.hpp"

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

    velocity->setAcceleration({-0.7, 0});
    if (velocity->getSpeed().x < -30)
        velocity->setAcceleration({-0.1, 0});
}

FloatingRobot::FloatingRobot(const Engine::Point<double> &pos) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<double>{pos, {SIZE_X, SIZE_Y}})), pos)
{
        this->addComponent<PatternComponent>(&pattern);
        this->addComponent<AutomaticWeaponComponent>(1, 0.5, 1, -100);
        this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<double>>>{
                {DEFAULT, {
                                  {_size.x * 0, _size.x * 1, 0, _size.y},
                                  {_size.x * 1, _size.x * 2, 0, _size.y},
                                  {_size.x * 2, _size.x * 3, 0, _size.y}}}
        }, true);
    this->addComponent<HealthComponent>(6);
    this->addComponent<Engine::ColliderComponent>(Collision::ENEMY, pos, _size);
}