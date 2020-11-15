//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_COLLECTIBLE_HPP
#define RTYPE_COLLECTIBLE_HPP

#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "graphical/ATexture.hpp"
#include "graphical/ASprite.hpp"
#include "components/TransformComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/CollectibleComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "dataHolders/DataSprite.hpp"
#include "CollisionMasks.hpp"

class Collectible : public Engine::Entity {
private:
    std::map<CollectibleComponent::Type, std::string> _collectibles = {
            {CollectibleComponent::Type::SENTINEL, "../../client/assets/images/weapons/power_up_1_100x20_24x20.png"},
            {CollectibleComponent::Type::MISSILE, "../../client/assets/images/bonus/bonus_1_160x36_40x36.png"},
            {CollectibleComponent::Type::DAMAGE, "../../client/assets/images/bonus/bonus_2_160x36_40x36.png"},
            {CollectibleComponent::Type::BOUNCE, "../../client/assets/images/bonus/bonus_3_160x36_40x36.png"}
    };
    std::map<CollectibleComponent::Type, std::vector<Engine::Box<double>>> _anims {
            {CollectibleComponent::Type::SENTINEL, {
                {{24 * 0, 0}, {24, 20}},
                {{24 * 1, 0}, {24, 20}},
                {{24 * 2, 0}, {24, 20}},
                {{24 * 3, 0}, {24, 20}}},},
            {CollectibleComponent::Type::BOUNCE, {
                {{40 * 0, 0}, {40, 36}},
                {{40 * 1, 0}, {40, 36}},
                {{40 * 2, 0}, {40, 36}},
                {{40 * 3, 0}, {40, 36}}},},
            {CollectibleComponent::Type::DAMAGE, {
                {{40 * 0, 0}, {40, 36}},
                {{40 * 1, 0}, {40, 36}},
                {{40 * 2, 0}, {40, 36}},
                {{40 * 3, 0}, {40, 36}}},},
            {CollectibleComponent::Type::MISSILE, {
                {{40 * 0, 0}, {40, 36}},
                {{40 * 1, 0}, {40, 36}},
                {{40 * 2, 0}, {40, 36}},
                {{40 * 3, 0}, {40, 36}}}},
    };
public:
    explicit Collectible(const Engine::Point<double> &pos, CollectibleComponent::Type type) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(_collectibles[type], _anims[type][0]);

        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>(Engine::Point<double>{-15, 0});
        this->addComponent<Engine::AnimationComponent>(0.2);
        this->addComponent<Engine::ColliderComponent>(Collision::BONUS, pos, _anims[type][0].size);
        this->addComponent<Engine::SpriteComponent>(10, std::move(spr));
        this->addComponent<CollectibleComponent>(1, type);
        this->getComponent<Engine::AnimationComponent>()->addAnimation(0, _anims[type]);
        this->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    }
};

#endif //RTYPE_COLLECTIBLE_HPP
