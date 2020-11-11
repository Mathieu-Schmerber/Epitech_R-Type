//
// Created by mathi on 07/11/2020.
//

#include <iostream>
#include <algorithm>
#include "systems/TextSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/TextComponent.hpp"

Engine::TextSystem::TextSystem(std::shared_ptr<Engine::AWindow> &window) : _window(window), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::TextComponent>();
}

bool Engine::TextSystem::compare(const std::shared_ptr<Engine::Entity> &a, const std::shared_ptr<Engine::Entity> &b)
{
    return a->getComponent<TextComponent>()->getLayer() < b->getComponent<TextComponent>()->getLayer();
}

void Engine::TextSystem::update()
{
    Engine::TransformComponent *transform = nullptr;

    std::sort(this->_entities.begin(), this->_entities.end(), this->compare);
    for (auto &e : this->_entities) {
        transform = e->getComponent<Engine::TransformComponent>();
        for (auto &txt : e->getComponents<Engine::TextComponent>())
            txt->draw(_window, transform->getPos(), static_cast<float>(transform->getRotation()));
    }
}