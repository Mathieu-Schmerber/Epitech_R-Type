//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include "systems/DrawSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

Engine::DrawSystem::DrawSystem(Engine::AWindow *window) : _window(window), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::SpriteComponent>();
}

void Engine::DrawSystem::update()
{
    Engine::TransformComponent *transform = nullptr;

    for (auto e : this->_entities) {
        transform = e.get()->getComponent<Engine::TransformComponent>();
        std::cout << "Draw at " << transform->getPos().first << ":" << transform->getPos().second << std::endl;
        //TODO: this->_window->draw(position, sprite) ?
    }
}