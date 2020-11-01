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

    for (auto &e : this->_entities) {
        transform = e->getComponent<Engine::TransformComponent>();
        std::cout << "Draw at " << transform->getPos().x << ":" << transform->getPos().y << std::endl;
        e.get()->getComponent<Engine::SpriteComponent>()->getSprite()->draw(_window, e.get()->getComponent<Engine::TransformComponent>()->getPos(), e.get()->getComponent<Engine::TransformComponent>()->getRotation());
        //TODO: this->_window->draw(position, sprite) ?
    }
}