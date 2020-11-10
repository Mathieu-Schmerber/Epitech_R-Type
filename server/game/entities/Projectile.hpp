//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_PROJECTILE_HPP
#define RTYPE_PROJECTILE_HPP

#include "tools/Geometry.hpp"
#include "graphical/ATexture.hpp"
#include "graphical/ASprite.hpp"
#include "ecs/Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "../components/ProjectileComponent.hpp"
#include "../dataHolders/DataSprite.hpp"

class Projectile : public Engine::Entity {
public:
    explicit Projectile(Engine::Point<int> pos, Engine::Point<int> size, Engine::Vector<double> speed, double damage, double lifetime,
                        std::shared_ptr<Engine::ATexture> &texture) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(texture, Engine::Box<int>{{0, 0}, {size.x, size.y}});
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>(speed);
        this->addComponent<Engine::ColliderComponent>(0, Engine::Box<double>{{0, 0}, {(double)size.x, (double)size.y}});
        this->addComponent<Engine::AnimationComponent>();
        this->addComponent<Engine::SpriteComponent>(0, std::move(spr));
        this->addComponent<ProjectileComponent>(damage, lifetime);
    }
};

#endif //RTYPE_PROJECTILE_HPP