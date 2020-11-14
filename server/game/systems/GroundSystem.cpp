//
// Created by mathi on 12/11/2020.
//

#include "tools/RandomETU.hpp"
#include "GroundSystem.hpp"

GroundSystem::GroundSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::ParallaxComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::ColliderComponent>();
}

void GroundSystem::spawnGrounds(double xOffset, double yOffset)
{
    auto height = Engine::RandomETU::randETU<int, int>(1, 2);
    std::shared_ptr<Engine::Entity> gr;
    Engine::Point<double> pos = {0, 0};

    for (int j = 1; j < height + 1; j++) {
        pos = {xOffset, yOffset + (GROUND_HEIGHT * (j - 1))};
        gr = std::make_shared<Ground>(pos, Engine::Point<double>{-GROUND_WIDTH, pos.y}, Engine::Vector<double>{-20, 0});
        this->_game->spawn(gr, true);
    }
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
            this->spawnGrounds(i * GROUND_WIDTH, 0);
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
        this->spawnGrounds(GROUND_WIDTH * 9, 0);
}