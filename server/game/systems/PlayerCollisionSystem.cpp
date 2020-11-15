//
// Created by mathi on 14/11/2020.
//

#include <algorithm>
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
    this->addDependency<HealthComponent>();
    this->addDependency<ManualWeaponComponent>();
}

std::vector<std::shared_ptr<Engine::Entity>> PlayerCollisionSystem::getSentinels(std::shared_ptr<Engine::Entity> &player) const
{
    std::vector<std::shared_ptr<Engine::Entity>> res;
    auto children = player->getComponent<Engine::ChildrenComponent>();

    for (auto &child : children->getChildren()) {
        if (child->getComponent<AutomaticWeaponComponent>())
            res.push_back(child);
    }
    std::sort(res.begin(), res.end(), [](std::shared_ptr<Engine::Entity> &a, std::shared_ptr<Engine::Entity> &b) -> bool {
        return a->getComponent<AutomaticWeaponComponent>()->getMultiplier() < b->getComponent<AutomaticWeaponComponent>()->getMultiplier();
    });
    return res;
}

void PlayerCollisionSystem::attachSentinel(std::shared_ptr<Engine::Entity> &player, bool top)
{
    std::shared_ptr<Engine::Entity> sentinel = std::make_shared<Sentinel>(Engine::Point<double>{0, 0});
    auto box1 = player->getComponent<Engine::ColliderComponent>()->getHitBox();
    auto box2 = sentinel->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto pos = (top ? Engine::Geometry::placeTop(box1, box2) : Engine::Geometry::placeBottom(box1, box2));
    auto offset = Engine::Point<double>{0.0, (top ? -10.0 : 10.0)};
    player->getComponent<HealthComponent>()->gainHealth(1);

    pos = {pos.x + offset.x, pos.y + offset.y};
    sentinel->getComponent<Engine::TransformComponent>()->setPos(pos);
    player->getComponent<Engine::ChildrenComponent>()->addChild(sentinel);
    this->_game->spawn(sentinel, true);
}

bool PlayerCollisionSystem::hasPowerUp(std::shared_ptr<Engine::Entity> &sentinel, CollectibleComponent::Type type)
{
    for (auto &weapon : sentinel->getComponents<AutomaticWeaponComponent>()) {
        switch (type) {
            case CollectibleComponent::Type::DAMAGE:
                if (weapon->getMultiplier() == 3)
                    return true;
                break;
            case CollectibleComponent::Type::MISSILE:
                if (weapon->useTargets())
                    return true;
                break;
            case CollectibleComponent::Type::BOUNCE:
                if (weapon->canBounce())
                    return true;
                break;
            default:
                return false;
        }
    }
    return false;
}

void PlayerCollisionSystem::powerDamage(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel)
{
    auto weapon = sentinel->getComponent<AutomaticWeaponComponent>();
    auto box1 = player->getComponent<Engine::ColliderComponent>()->getHitBox();
    Engine::Box<double> box2 = {0, 0, 0, 0};
    double top = (sentinel->getComponent<Engine::TransformComponent>()->getPos().y > player->getComponent<Engine::TransformComponent>()->getPos().y ? 1 : -1);

    if (weapon->getMultiplier() == 3)
        return;
    weapon->setDamageMultiplier(weapon->getMultiplier() + 1);
    sentinel->getComponent<Engine::AnimationComponent>()->setAnimation(static_cast<int>(weapon->getMultiplier() - 1), true);
    box2 = sentinel->getComponent<Engine::AnimationComponent>()->getNextFrame();
    if (top == -1)
        sentinel->getComponent<Engine::TransformComponent>()->setPos(Engine::Geometry::placeTop(box1, box2));
    else
        sentinel->getComponent<Engine::TransformComponent>()->setPos(Engine::Geometry::placeBottom(box1, box2));
}

void PlayerCollisionSystem::powerBounce(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel)
{
    double top = (sentinel->getComponent<Engine::TransformComponent>()->getPos().y > player->getComponent<Engine::TransformComponent>()->getPos().y ? 1 : -1);
    auto added = sentinel->addComponent<AutomaticWeaponComponent>(1, 1, Engine::Vector<double>{40.0, 45 * top},
                                                               Collision::Mask::PLAYER_PROJECTILE, ProjectileComponent::Type::SHURIKEN);
    added->setBounce(true);
}

void PlayerCollisionSystem::powerMissile(std::shared_ptr<Engine::Entity> &player, std::shared_ptr<Engine::Entity> &sentinel)
{
    auto added = sentinel->addComponent<AutomaticWeaponComponent>(1, 2,Engine::Vector<double>{20.0, 0},
                                                                  Collision::Mask::PLAYER_PROJECTILE, ProjectileComponent::Type::MISSILE);
    added->setUseTargets(true);
}

void PlayerCollisionSystem::applyPowerUp(std::shared_ptr<Engine::Entity> &player, CollectibleComponent::Type type)
{
    auto sentinels = PlayerCollisionSystem::getSentinels(player);
    void (PlayerCollisionSystem::*f[])(std::shared_ptr<Engine::Entity> &, std::shared_ptr<Engine::Entity> &) = {
            &PlayerCollisionSystem::powerDamage,
            &PlayerCollisionSystem::powerBounce,
            &PlayerCollisionSystem::powerMissile
    };

    for (auto &child : sentinels) {
        if (child->getComponent<AutomaticWeaponComponent>() && !PlayerCollisionSystem::hasPowerUp(child, type)) {
            (this->*f[type - 1])(player, child);
            return;
        }
    }
}

void PlayerCollisionSystem::pickupCollectible(std::shared_ptr<Engine::Entity> &player, CollectibleComponent::Type type, double value)
{
    int sentinelCount = 0;
    auto children = player->getComponent<Engine::ChildrenComponent>()->getChildren();

    if (type == CollectibleComponent::Type::SENTINEL) {
        for (auto &child : children)
            sentinelCount += (child->getComponent<AutomaticWeaponComponent>() != nullptr);
        if (sentinelCount < 2)
            this->attachSentinel(player, (sentinelCount == 0));
    } else
            PlayerCollisionSystem::applyPowerUp(player, type);
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
    for (auto &e : this->_entities) {
        this->handleCollisions(e);
        auto sentinels = PlayerCollisionSystem::getSentinels(e);
        if (e->getComponent<HealthComponent>()->getCurrentHealth() - 1 < sentinels.size() &&
            e->getComponent<HealthComponent>()->getCurrentHealth() > 0) {
            for (size_t i = static_cast<int>(e->getComponent<HealthComponent>()->getCurrentHealth()) - 1; i < sentinels.size(); ++i)
                this->_game->despawn(sentinels[0]);
        }
    }
}