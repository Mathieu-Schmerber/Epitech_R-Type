//
// Created by mathi on 07/11/2020.
//

#include "tools/Utils.hpp"
#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem() : Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
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
    const double speed = 3;
    auto pressed = player->getComponent<Engine::ControllerComponent>()->getPressed();
    Engine::Vector<double> dir = {0, 0};

    dir.x -= (Engine::Utils::isInVector(pressed, Engine::Inputs::Left));
    dir.x += (Engine::Utils::isInVector(pressed, Engine::Inputs::Right));
    dir.y -= (Engine::Utils::isInVector(pressed, Engine::Inputs::Up));
    dir.y += (Engine::Utils::isInVector(pressed, Engine::Inputs::Down));
    //TODO: debug
    std::cout << "Right: " << Engine::Inputs::Right << std::endl;
    for (auto &i : pressed)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "dir: " << dir.x << ":" << dir.y << std::endl;
    //TODO: debug
    dir = {dir.x * speed, dir.y * speed};
    handleMoveAnimations(player, dir);
    player->getComponent<Engine::VelocityComponent>()->setSpeed(dir);
}

void PlayerSystem::handleCollisions(std::shared_ptr<Engine::Entity> &player)
{

}

void PlayerSystem::handleWeapon(std::shared_ptr<Engine::Entity> &player)
{

}

void PlayerSystem::update()
{
    for (auto &e : this->_entities) {
        this->handleMovements(e);
        this->handleWeapon(e);
        this->handleCollisions(e);
    }
}