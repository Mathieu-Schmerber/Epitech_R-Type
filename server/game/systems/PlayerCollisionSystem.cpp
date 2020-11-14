//
// Created by mathi on 14/11/2020.
//

#include "PlayerCollisionSystem.hpp"
#include "CollisionMasks.hpp"
#include "entities/Sentinel.hpp"

PlayerCollisionSystem::PlayerCollisionSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<Engine::ChildrenComponent>();
    this->addDependency<ManualWeaponComponent>();
}

void PlayerCollisionSystem::attachSentinel(std::shared_ptr<Engine::Entity> &player, bool top)
{
    std::shared_ptr<Engine::Entity> sentinel = std::make_shared<Sentinel>(Engine::Point<double>{0, 0});
    auto box1 = player->getComponent<Engine::ColliderComponent>()->getHitBox();
    auto box2 = sentinel->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto pos = (top ? Engine::Geometry::placeTop(box1, box2) : Engine::Geometry::placeBottom(box1, box2));
    auto offset = Engine::Point<double>{0.0, (top ? -10.0 : 10.0)};

    pos = {pos.x + offset.x, pos.y + offset.y};
    sentinel->getComponent<Engine::TransformComponent>()->setPos(pos);
    player->getComponent<Engine::ChildrenComponent>()->addChild(sentinel);
    this->_game->spawn(sentinel, true);
}

void PlayerCollisionSystem::pickupCollectible(std::shared_ptr<Engine::Entity> &player, CollectibleComponent::Type type, double value)
{
    int sentinelCount = 0;
    auto children = player->getComponent<Engine::ChildrenComponent>()->getChildren();

    for (auto &child : children)
        sentinelCount += (child->getComponent<AutomaticWeaponComponent>() != nullptr);
    if (sentinelCount < 2)
        this->attachSentinel(player, (sentinelCount == 0));
}

void PlayerCollisionSystem::handleCollisions(std::shared_ptr<Engine::Entity> &player)
{
    auto collider = player->getComponent<Engine::ColliderComponent>();
    auto collisions = collider->getCollisions();
    auto collided = Collision::removeIgnored(static_cast<Collision::Mask>(collider->getCollisionMask()), collisions);
    Engine::ColliderComponent *other = nullptr;
    auto copy = collided;

    for (auto &c : copy) {
        other = c->getComponent<Engine::ColliderComponent>();
        switch (other->getCollisionMask()) {
            case Collision::Mask::BONUS:
                auto collectible = c->getComponent<CollectibleComponent>();
                if (collectible)
                    PlayerCollisionSystem::pickupCollectible(player, collectible->getType(), collectible->getBonusValue());
                this->_game->despawn(c);
                break;
        }
    }
}

void PlayerCollisionSystem::update()
{
    for (auto &e : this->_entities)
        this->handleCollisions(e);
}