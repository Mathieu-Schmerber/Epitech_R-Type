//
// Created by mathi on 14/11/2020.
//

#ifndef RTYPE_PLAYERCOLLISIONSYSTEM_HPP
#define RTYPE_PLAYERCOLLISIONSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Player.hpp"
#include "components/CollectibleComponent.hpp"
#include "Game.hpp"

class PlayerCollisionSystem : public Engine::System
{
private:
    std::shared_ptr<Game> _game;

    void powerDamage(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel);
    void powerBounce(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel);
    void powerMissile(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel);

    void attachSentinel(std::shared_ptr<Engine::Entity> &player, bool top);
    static bool hasPowerUp(std::shared_ptr<Engine::Entity> &sentinel, CollectibleComponent::Type type);
    void applyPowerUp(std::shared_ptr<Engine::Entity> &player, CollectibleComponent::Type type);
    void pickupCollectible(std::shared_ptr<Engine::Entity> &player, CollectibleComponent::Type type, double value);
    void handleCollisions(std::shared_ptr<Engine::Entity> &player);
public:
    explicit PlayerCollisionSystem(std::shared_ptr<Game> &game);

    void update() override;
};

#endif //RTYPE_PLAYERCOLLISIONSYSTEM_HPP
