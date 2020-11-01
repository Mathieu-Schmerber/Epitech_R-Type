//
// Created by mathi on 01/11/2020.
//

#include "systems/MouseSystem.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"

Engine::MouseSystem::MouseSystem(std::shared_ptr<Engine::AEvents> &events) : _events(events), Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::MouseSystem::update()
{
    Point<int> mousePos = {0, 0}; // TODO: mousePos = this->_events->getMousePos()

    // TODO: if window's inputs contains Engine::Key::LeftClick
    for (auto &e : this->_entities) {
        auto transform = e->getComponent<TransformComponent>();
        auto sprite = e->getComponent<SpriteComponent>();
        auto clickable = e->getComponent<ClickableComponent>();
        Box<int> box = Box<int>(transform->getPos(), sprite->getSprite()->getSize());

        if (Geometry::doOverlap(mousePos, box))
            clickable->onClick();
    }
}