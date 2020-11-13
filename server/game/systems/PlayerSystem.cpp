//
// Created by mathi on 07/11/2020.
//

#include "tools/Utils.hpp"
#include "PlayerSystem.hpp"
#include "entities/Projectile.hpp"
#include "entities/Particle.hpp"

PlayerSystem::PlayerSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
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

bool PlayerSystem::willExitScreen(Engine::Point<double> pos, Engine::Vector<double> dir)
{
    Engine::Box<double> screen = {{0, 0}, {1920, 1080}};
    Engine::Point<double> res = {pos.x + dir.x, pos.y + dir.y};

    return !Engine::Geometry::doOverlap(res, screen);
}

void PlayerSystem::handleMoveAnimations(std::shared_ptr<Engine::Entity> &player, Engine::Vector<double> dir)
{
    if (dir.y > 0)
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::DOWN, false);
    else if (dir.y < 0)
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::UP, false);
    else
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::IDLE);
}

void PlayerSystem::handleMovements(std::shared_ptr<Engine::Entity> &player)
{
    const double speed = 20;
    auto pressed = player->getComponent<Engine::ControllerComponent>()->getPressed();
    auto center = player->getComponent<Engine::ColliderComponent>()->getHitBox().center;
    Engine::Vector<double> dir = {0, 0};

    dir.x -= (Engine::Utils::isInVector(pressed, Engine::Inputs::Left));
    dir.x += (Engine::Utils::isInVector(pressed, Engine::Inputs::Right));
    dir.y -= (Engine::Utils::isInVector(pressed, Engine::Inputs::Up));
    dir.y += (Engine::Utils::isInVector(pressed, Engine::Inputs::Down));
    Engine::Geometry::normalizeVector(dir);
    dir = {dir.x * speed, dir.y * speed};
    handleMoveAnimations(player, dir);
    if (!PlayerSystem::willExitScreen(center, dir))
        player->getComponent<Engine::VelocityComponent>()->setSpeed(dir);
    else
        player->getComponent<Engine::VelocityComponent>()->setSpeed({0, 0});
}

void PlayerSystem::handleCollisions(std::shared_ptr<Engine::Entity> &player)
{
    auto collisions = player->getComponent<Engine::ColliderComponent>()->getCollisions();

    for (auto &c : collisions) {

    }
}

void PlayerSystem::spawnShootParticle(std::shared_ptr<Engine::Entity> &player)
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

void PlayerSystem::destroyShootParticle(std::shared_ptr<Engine::Entity> &player)
{
    auto children = player->getComponent<Engine::ChildrenComponent>();

    for (auto &child : children->getChildren()) {
        if (child->getComponent<Engine::SpriteComponent>() &&
        child->getComponent<Engine::SpriteComponent>()->getTexture() == this->_shootParticle)
            this->_game->despawn(child);
    }
}

std::shared_ptr<Engine::Entity> PlayerSystem::generateProjectile(ManualWeaponComponent *weapon)
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
                 Engine::Vector<double>{40 * (key / 2.0), 0},weapon->getCurrentDamages() * chargeMultiplier, 2,
                       this->_projectileTextures[key]);
    projectile->getComponent<Engine::AnimationComponent>()->addAnimation(0, this->_chargeTypes[key].second);
    projectile->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    projectile->getComponent<Engine::ColliderComponent>()->setHitBox(this->_chargeTypes[key].second[0]);
    projectile->getComponent<Engine::ColliderComponent>()->setBaseHitBox(this->_chargeTypes[key].second[0]);
    return projectile;
}

void PlayerSystem::handleWeapon(std::shared_ptr<Engine::Entity> &player)
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

void PlayerSystem::update()
{
    for (auto &e : this->_entities) {
        this->handleMovements(e);
        this->handleWeapon(e);
        this->handleCollisions(e);
    }
}