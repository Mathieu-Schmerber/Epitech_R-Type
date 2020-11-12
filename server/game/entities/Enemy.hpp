/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_IENEMY_HPP
#define RTYPE_IENEMY_HPP

#include "ecs/Entity.hpp"
#include "dataHolders/DataSprite.hpp"
#include "components/ManualWeaponComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/ColliderComponent.hpp"

class Enemy : public Engine::Entity {
public:
    explicit Enemy(std::unique_ptr<Engine::ASprite> sprite, const Engine::Point<float> &pos = {0, 0}) : Engine::Entity()
    {
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>();
        this->addComponent<Engine::SpriteComponent>(1, std::move(sprite));
        this->addComponent<Engine::ControllerComponent>();
        this->addComponent<Engine::ColliderComponent>();
    }

    enum enemyState {
        DEFAULT
    };
};

#endif //RTYPE_IENEMY_HPP
