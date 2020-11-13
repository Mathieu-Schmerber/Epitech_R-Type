/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_SPAWNER_HPP
#define RTYPE_SPAWNER_HPP

#include "ecs/Entity.hpp"
#include "dataHolders/DataSprite.hpp"
#include "components/ManualWeaponComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/EnemySpawnerComponent.hpp"

class Spawner : public Engine::Entity {
public:
    explicit Spawner(const Engine::Point<double> &pos = {1920, 1080.0 / 2.0}, double spawnRate = 5) : Engine::Entity()
    {
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>(Engine::Vector<double>({0, 0}));
        this->addComponent<Engine::ColliderComponent>();
        this->addComponent<EnemySpawnerComponent>(spawnRate);
    }
};

#endif //RTYPE_SPAWNER_HPP
