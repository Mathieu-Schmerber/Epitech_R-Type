//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include "systems/DrawSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

Engine::DrawSystem::DrawSystem(std::shared_ptr<Engine::AWindow> &window) : _window(window), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::SpriteComponent>();
}

void Engine::DrawSystem::update()
{
    Engine::TransformComponent *transform = nullptr;
    Engine::SpriteComponent *sprite = nullptr;

    for (auto &e : this->_entities) {
        transform = e->getComponent<Engine::TransformComponent>();
        sprite = e->getComponent<Engine::SpriteComponent>();
        sprite->getSprite()->draw(_window, transform->getPos(), static_cast<float>(transform->getRotation()));
    }
}