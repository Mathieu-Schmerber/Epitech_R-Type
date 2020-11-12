//
// Created by mathi on 12/11/2020.
//

#include <random>
#include "GroundSystem.hpp"

GroundSystem::GroundSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::ParallaxComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->_lastHeight = 1;
}

void GroundSystem::spawnGrounds(int offset)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(-1, 1);
    auto height = uni(rng) + this->_lastHeight;
    std::shared_ptr<Engine::Entity> gr;
    Engine::Point<int> pos = {0, 0};

    height = (height > 3 ? 2 : (height == 0 ? 1 : height));
    for (int j = 1; j < height + 1; j++) {
        pos = {offset, 1080 - (GROUND_HEIGHT * j)};
        gr = std::make_shared<Ground>(pos, Engine::Point<int>{-GROUND_WIDTH, pos.y}, Engine::Vector<double>{-20, 0});
        this->_game->spawn(gr, true);
    }
    this->_lastHeight = height;
}

void GroundSystem::update()
{
    Engine::TransformComponent *transform;
    Engine::VelocityComponent *velocity;
    Engine::ParallaxComponent *parallax;
    auto copy = this->_entities;
    bool spawned = false;

    if (this->_entities.empty()) {
        for (int i = 0; i < 1920 / GROUND_WIDTH + 1; ++i)
            this->spawnGrounds(i * GROUND_WIDTH);
    }
    for (auto &e : copy) {
        transform = e->getComponent<Engine::TransformComponent>();
        velocity = e->getComponent<Engine::VelocityComponent>();
        parallax = e->getComponent<Engine::ParallaxComponent>();
        if (parallax->isLimitReached(transform->getPos(), velocity->getSpeed())) {
            spawned = true;
            this->_game->despawn(e);
        }
    }
    if (spawned)
        this->spawnGrounds(GROUND_WIDTH * 10);
}