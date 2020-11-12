//
// Created by mathi on 02/11/2020.
//

#include "systems/ParallaxSystem.hpp"
#include "components/ParallaxComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/TransformComponent.hpp"

Engine::ParallaxSystem::ParallaxSystem() : Engine::System()
{
    this->addDependency<ParallaxComponent>();
    this->addDependency<VelocityComponent>();
    this->addDependency<TransformComponent>();
}

void Engine::ParallaxSystem::update()
{
    ParallaxComponent *parallax = nullptr;
    VelocityComponent *velocity = nullptr;
    TransformComponent *transform = nullptr;

    for (auto &e : this->_entities) {
        parallax = e->getComponent<ParallaxComponent>();
        velocity = e->getComponent<VelocityComponent>();
        transform = e->getComponent<TransformComponent>();
        if (parallax->isLimitReached(static_cast<Point<float>>(transform->getPos()), velocity->getSpeed()) && parallax->isAutomatic())
            transform->setPos(static_cast<Point<float>>(parallax->getStart()));
    }
}