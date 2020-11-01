//
// Created by mathi on 01/11/2020.
//

#include "systems/MouseSystem.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"

Engine::MouseSystem::MouseSystem(Engine::AWindow *window) : _window(window), Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::MouseSystem::update()
{
    Point<int> mousePos; // TODO: mousePos = this->_window->getMousePos()

    // TODO: if window's inputs contains Engine::Key::LeftClick
    for (auto &e : this->_entities) {
        auto transform = e.get()->getComponent<TransformComponent>();
        auto sprite = e.get()->getComponent<SpriteComponent>();
        auto clickable = e.get()->getComponent<ClickableComponent>();
        Box<int> box = Box<int>(transform->getPos(), sprite->getDisplay()->getSize());

        if (Geometry::doOverlap(mousePos, box))
            clickable->onClick();
    }
}