//
// Created by mathi on 07/11/2020.
//

#include "tools/Utils.hpp"
#include "PlayerSystem.hpp"
#include "entities/Projectile.hpp"

PlayerSystem::PlayerSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<ManualWeaponComponent>();
    this->_projectileTexture = std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_1_72x18_18x18.png");
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

}

void PlayerSystem::handleWeapon(std::shared_ptr<Engine::Entity> &player)
{
    auto pressed = player->getComponent<Engine::ControllerComponent>()->getPressed();
    auto weapon = player->getComponent<ManualWeaponComponent>();
    auto transform = player->getComponent<Engine::TransformComponent>();

    if (Engine::Utils::isInVector(pressed, Engine::Inputs::Space) && weapon->canShoot()) {
        weapon->refreshShoots();
        std::shared_ptr<Engine::Entity> projectile = std::make_shared<Projectile>(
                transform->getPos(), Engine::Point<double>{18, 18}, Engine::Vector<double>{40, 0},
                weapon->getCurrentDamages(), 2,this->_projectileTexture);
        this->_game->spawn(projectile, true);
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