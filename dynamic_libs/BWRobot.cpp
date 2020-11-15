/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "entities/Ground.hpp"
#include "CollisionMasks.hpp"
#include "components/ProjectileComponent.hpp"
#include "BWRobot.hpp"
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
        return new BWRobot();
    }
}

void pattern(std::shared_ptr<Engine::Entity> &enemy)
{
    auto velocity = enemy->getComponent<Engine::VelocityComponent>();
    auto transform = enemy->getComponent<Engine::TransformComponent>();
    auto animation = enemy->getComponent<Engine::AnimationComponent>();

    transform->setPos(Engine::Point<double>({transform->getPos().x, 1080 - SIZE_Y - GROUND_HEIGHT + ADJUSTMENT}));
    if (Engine::RandomETU::randETU(100) == Engine::RandomETU::randETU(100)) {
        if (velocity->getSpeed().x > 0)
            velocity->setSpeed(Engine::Vector<double>(velocity->getSpeed() * Engine::Vector<double>({-1, 1})) + Engine::Vector<double>({FLOOR_SPEED, 0}));
        else
            velocity->setSpeed(Engine::Vector<double>(velocity->getSpeed() * Engine::Vector<double>({-1, 1})) + Engine::Vector<double>({FLOOR_SPEED, 0}));

        animation->setAnimation(!animation->getAnimation(), true);
    }
}

BWRobot::BWRobot(const Engine::Point<double> &pos) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<double>{pos, {SIZE_X, SIZE_Y}})), pos)
{
    this->addComponent<PatternComponent>(&pattern);
    this->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{-40, 0}, Collision::Mask::ENEMY_PROJECTILE, ProjectileComponent::Type::BASIC);
    this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<double>>>{
            {DEFAULT, {
                              {_size.x * 0, _size.x * 1, 0, _size.y},
                              {_size.x * 1, _size.x * 2, 0, _size.y},
                              {_size.x * 2, _size.x * 3, 0, _size.y}}},
            {REVERSE, {
                              {_size.x * 0, _size.x * 1, _size.y, _size.y * 2},
                              {_size.x * 1, _size.x * 2, _size.y, _size.y * 3},
                              {_size.x * 2, _size.x * 3, _size.y, _size.y * 4}}}
    }, true);
    this->addComponent<HealthComponent>(2);
    this->addComponent<Engine::ColliderComponent>(Collision::ENEMY, pos, _size);
    this->addComponent<Engine::VelocityComponent>(Engine::Vector<double>({-5 + FLOOR_SPEED, 0}), Engine::Vector<double>({0, 0}));
    this->addComponent<Engine::TargetComponent>();
}