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
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/AutomaticWeaponComponent.hpp"
#include "dataHolders/DataSprite.hpp"

#define SENTINEL_FILE "../../client/assets/images/weapons/sentinel_204x17_17x17.png"

class Sentinel : public Engine::Entity {
private:
    std::vector<Engine::Box<double>> _anims {
            {{17 * 0, 0}, {17, 17}},
            {{17 * 1, 0}, {17, 17}},
            {{17 * 2, 0}, {17, 17}},
            {{17 * 3, 0}, {17, 17}},
            {{17 * 4, 0}, {17, 17}},
            {{17 * 5, 0}, {17, 17}},
            {{17 * 6, 0}, {17, 17}},
            {{17 * 7, 0}, {17, 17}},
            {{17 * 8, 0}, {17, 17}},
            {{17 * 9, 0}, {17, 17}},
            {{17 * 10, 0}, {17, 17}},
            {{17 * 11, 0}, {17, 17}}};
public:
    explicit Sentinel(const Engine::Point<double> &pos) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(SENTINEL_FILE, _anims[0]);

        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::AnimationComponent>(0.1);
        this->addComponent<Engine::SpriteComponent>(10, std::move(spr));
        this->addComponent<AutomaticWeaponComponent>(5.0, 1.0, 0.5, 50.0, Collision::Mask::PLAYER_PROJECTILE, ProjectileComponent::Type::BASIC);
        this->getComponent<Engine::AnimationComponent>()->addAnimation(0, _anims);
        this->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    }
};

#endif //RTYPE_COLLECTIBLE_HPP
