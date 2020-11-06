//
// Created by mathi on 06/11/2020.
//

#include "systems/WindowResizeSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

Engine::WindowResizeSystem::WindowResizeSystem(std::shared_ptr<AWindow> &window) : _window(window), Engine::System()
{
    this->_lastSize = window->getSize();
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
}

void Engine::WindowResizeSystem::update()
{
    //TODO: implement that stuff correctly
    /*auto current = this->_window->getSize();
    auto ratio = Scale<int>{current.x / _lastSize.x, current.y / _lastSize.y};

    if (current == this->_lastSize)
        return;
    for (auto &e : this->_entities) {
        auto pos = e->getComponent<TransformComponent>()->getPos();
        e->getComponent<TransformComponent>()->setPos({pos.x * ratio.x, pos.y * ratio.y});
    }*/
}