//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_PARTICLE_HPP
#define RTYPE_PARTICLE_HPP

#include "CollisionMasks.hpp"
#include "tools/Geometry.hpp"
#include "graphical/ATexture.hpp"
#include "graphical/ASprite.hpp"
#include "ecs/Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/LifetimeComponent.hpp"
#include "dataHolders/DataSprite.hpp"

class Particle : public Engine::Entity {
public:
    explicit Particle(Engine::Point<double> pos, double lifetime, std::shared_ptr<Engine::ATexture> &texture) : Engine::Entity()
    {
        std::unique_ptr<Engine::ASprite> spr = std::make_unique<DataSprite>(texture);

        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::AnimationComponent>();
        this->addComponent<Engine::SpriteComponent>(10, std::move(spr));
        this->addComponent<LifetimeComponent>(lifetime);
    }
};

#endif //RTYPE_PARTICLE_HPP