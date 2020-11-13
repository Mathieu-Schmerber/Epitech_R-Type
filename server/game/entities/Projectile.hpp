//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_PROJECTILE_HPP
#define RTYPE_PROJECTILE_HPP

#include "CollisionMasks.hpp"
#include "tools/Geometry.hpp"
#include "graphical/ATexture.hpp"
#include "graphical/ASprite.hpp"
#include "ecs/Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/LifetimeComponent.hpp"
#include "dataHolders/DataSprite.hpp"

class Projectile : public Engine::Entity {
public:
    explicit Projectile(Engine::Point<double> pos, Engine::Point<double> size, Engine::Vector<double> speed, double damage, double lifetime,
                        std::shared_ptr<Engine::ATexture> &texture) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(texture, Engine::Box<double>{{0, 0}, {size.x, size.y}});
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>(speed);
        this->addComponent<Engine::ColliderComponent>(Collision::PLAYER, pos, size);
        this->addComponent<Engine::AnimationComponent>();
        this->addComponent<Engine::SpriteComponent>(0, std::move(spr));
        this->addComponent<ProjectileComponent>(damage);
        this->addComponent<LifetimeComponent>(lifetime);
    }
};

#endif //RTYPE_PROJECTILE_HPP