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

class Spawner : public Engine::Entity {
public:
    explicit Spawner(const Engine::Point<double> &pos = {0, 0}) : Engine::Entity()
    {
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>();
        this->addComponent<Engine::ColliderComponent>();
    }
};

#endif //RTYPE_SPAWNER_HPP
