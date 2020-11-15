//
// Created by mathi on 07/11/2020.
//

#include "tools/Utils.hpp"
#include "PlayerMovementSystem.hpp"
#include "CollisionMasks.hpp"
#include "systems/GroundSystem.hpp"

PlayerMovementSystem::PlayerMovementSystem() : Engine::System()
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

bool PlayerMovementSystem::willExitScreen(Engine::Point<double> pos, Engine::Vector<double> dir)
{
    Engine::Box<double> screen = {{0, 0}, {1920, 1080 - (GROUND_HEIGHT + 10)}};
    Engine::Point<double> res = {pos.x + dir.x, pos.y + dir.y};

    return !Engine::Geometry::doOverlap(res, screen);
}

void PlayerMovementSystem::handleMoveAnimations(std::shared_ptr<Engine::Entity> &player, Engine::Vector<double> dir)
{
    if (dir.y > 0)
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::DOWN, false);
    else if (dir.y < 0)
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::UP, false);
    else
        player->getComponent<Engine::AnimationComponent>()->setAnimation(Player::PlayerState::IDLE);
}

void PlayerMovementSystem::handleMovements(std::shared_ptr<Engine::Entity> &player)
{
    const double speed = 30;
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
    if (!PlayerMovementSystem::willExitScreen(center, dir))
        player->getComponent<Engine::VelocityComponent>()->setSpeed(dir);
    else
        player->getComponent<Engine::VelocityComponent>()->setSpeed({0, 0});
}

void PlayerMovementSystem::update()
{
    for (auto &e : this->_entities)
        this->handleMovements(e);
}