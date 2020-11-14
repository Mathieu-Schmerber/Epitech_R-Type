//
// Created by mathi on 14/11/2020.
//

#include "PlayerWeaponSystem.hpp"
#include "tools/Utils.hpp"
#include "entities/Projectile.hpp"
#include "entities/Particle.hpp"
#include "CollisionMasks.hpp"
#include "entities/Sentinel.hpp"

PlayerWeaponSystem::PlayerWeaponSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<Engine::ChildrenComponent>();
    this->addDependency<ManualWeaponComponent>();
    for (auto &p : this->_chargeTypes)
        this->_projectileTextures[p.first] = std::make_shared<DataTexture>(p.second.first);
    this->_shootParticle = std::make_shared<DataTexture>("../../client/assets/images/explosions/charge_102x18_17x18.png");
}

void PlayerWeaponSystem::spawnShootParticle(std::shared_ptr<Engine::Entity> &player)
{
    auto box1 = player->getComponent<Engine::ColliderComponent>()->getHitBox();
    auto box2 = Engine::Box<double>{{0, 0}, {17, 18}};
    auto pos = Engine::Geometry::placeForward(box1, box2);
    pos = {pos.x + 5, pos.y};
    auto weapon = player->getComponent<ManualWeaponComponent>();
    auto children = player->getComponent<Engine::ChildrenComponent>();
    std::shared_ptr<Engine::Entity> particle = std::make_shared<Particle>(pos, 900, this->_shootParticle);
    auto animation = particle->getComponent<Engine::AnimationComponent>();

    animation->addAnimation(0, {
            {{17 * 0, 0}, {17, 18}}, {{17 * 1, 0}, {17, 18}},
            {{17 * 2, 0}, {17, 18}}, {{17 * 3, 0}, {17, 18}},
            {{17 * 4, 0}, {17, 18}}, {{17 * 5, 0}, {17, 18}}
    });
    animation->setAnimation(0, false);
    animation->setFrameTime((weapon->getMaxChargeTime() / 1000) / this->_chargeTypes.size());
    children->addChild(particle);
    this->_game->spawn(particle, true);
}

void PlayerWeaponSystem::destroyShootParticle(std::shared_ptr<Engine::Entity> &player)
{
    auto children = player->getComponent<Engine::ChildrenComponent>();

    for (auto &child : children->getChildren()) {
        if (child->getComponent<Engine::SpriteComponent>() &&
            child->getComponent<Engine::SpriteComponent>()->getTexture() == this->_shootParticle)
            this->_game->despawn(child);
    }
}

std::shared_ptr<Engine::Entity> PlayerWeaponSystem::generateProjectile(ManualWeaponComponent *weapon)
{
    int key = 1;
    double chargeMultiplier = Engine::Timer::getElapsed(weapon->getStartCharge()) / weapon->getMaxChargeTime();
    std::shared_ptr<Engine::Entity> projectile;

    chargeMultiplier = ceil((chargeMultiplier > 1 ? 1 : chargeMultiplier) * 10);
    for (auto &p : this->_chargeTypes) {
        if (p.first > chargeMultiplier)
            break;
        else if (p.first == chargeMultiplier) {
            key = p.first;
            break;
        }
        key = p.first;
    }
    projectile = std::make_shared<Projectile>(Engine::Point<double>{0, 0}, Engine::Point<double>{22, 18},
                                              Engine::Vector<double>{40, 0},weapon->getCurrentDamages() * chargeMultiplier, key + 1,
                                              this->_projectileTextures[key], Collision::PLAYER_PROJECTILE);
    projectile->getComponent<Engine::AnimationComponent>()->setFrameTime(0.2);
    projectile->getComponent<Engine::AnimationComponent>()->addAnimation(0, this->_chargeTypes[key].second);
    projectile->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    projectile->getComponent<Engine::ColliderComponent>()->setHitBox(this->_chargeTypes[key].second[0]);
    projectile->getComponent<Engine::ColliderComponent>()->setBaseHitBox(this->_chargeTypes[key].second[0]);
    projectile->getComponent<Engine::SpriteComponent>()->getSprite()->setRect(this->_chargeTypes[key].second[0]);
    projectile->getComponent<ProjectileComponent>()->setNbHit(key);
    return projectile;
}

void PlayerWeaponSystem::handleWeapon(std::shared_ptr<Engine::Entity> &player)
{
    auto pressed = player->getComponent<Engine::ControllerComponent>()->getPressed();
    auto weapon = player->getComponent<ManualWeaponComponent>();
    auto box = player->getComponent<Engine::ColliderComponent>()->getHitBox();

    if (Engine::Utils::isInVector(pressed, Engine::Inputs::Space) && !weapon->isCharging()) {
        weapon->beginCharge();
        this->spawnShootParticle(player);
    } else if (!Engine::Utils::isInVector(pressed, Engine::Inputs::Space) && weapon->isCharging() && weapon->canShoot()) {
        auto proj = this->generateProjectile(weapon);
        auto box2 = proj->getComponent<Engine::ColliderComponent>()->getHitBox();
        proj->getComponent<Engine::TransformComponent>()->setPos(Engine::Geometry::placeForward(box, box2));
        this->_game->spawn(proj, true);
        weapon->refreshShoots();
        weapon->abortCharge();
        this->destroyShootParticle(player);
    }
}

void PlayerWeaponSystem::update()
{
    for (auto &e : this->_entities)
        this->handleWeapon(e);
}