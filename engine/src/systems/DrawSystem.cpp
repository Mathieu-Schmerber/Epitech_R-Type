//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "DrawSystem.hpp"

Engine::DrawSystem::DrawSystem(Engine::AWindow *window) : _window(window), Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
}

void Engine::DrawSystem::update()
{
    TransformComponent *transform = nullptr;

    for (auto e : this->_entities) {
        transform = e.get()->getComponent<TransformComponent>();
        std::cout << "Draw at " << transform->getPos().first << ":" << transform->getPos().second << std::endl;
        //TODO: getComponent<SpriteComponent>()->draw()  ?
    }
}
