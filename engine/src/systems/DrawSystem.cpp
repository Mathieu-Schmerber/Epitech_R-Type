//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include <algorithm>
#include "systems/DrawSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

Engine::DrawSystem::DrawSystem(std::shared_ptr<Engine::AWindow> &window) : _window(window), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::SpriteComponent>();
}

bool Engine::DrawSystem::compare(const std::shared_ptr<Engine::Entity> &a, const std::shared_ptr<Engine::Entity> &b)
{
    return a->getComponent<SpriteComponent>()->getLayer() < b->getComponent<SpriteComponent>()->getLayer();
}

void Engine::DrawSystem::update()
{
    Engine::TransformComponent *transform = nullptr;
    Engine::SpriteComponent *sprite = nullptr;

    std::sort(this->_entities.begin(), this->_entities.end(), this->compare);
    for (auto &e : this->_entities) {
        transform = e->getComponent<Engine::TransformComponent>();
        for (auto &spr : e->getComponents<Engine::SpriteComponent>())
            spr->draw(_window, transform->getPos(), static_cast<float>(transform->getRotation()));
    }
}