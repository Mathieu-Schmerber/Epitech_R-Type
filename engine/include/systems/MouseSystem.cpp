//
// Created by mathi on 01/11/2020.
//

#include "MouseSystem.hpp"
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

    // TODO: if window's inputs contains Engine::Input::LeftClick
    for (auto &e : this->_entities) {
        auto transform = e.get()->getComponent<TransformComponent>();
        auto sprite = e.get()->getComponent<SpriteComponent>();
        auto clickable = e.get()->getComponent<ClickableComponent>();
        Box<int> box = {transform->getPos().x, transform->getPos().x + sprite->getSprite()->getSize().x,
                        transform->getPos().y, transform->getPos().y + sprite->getSprite()->getSize().y};

        if (Geometry::doOverlap(mousePos, box))
            clickable->onClick();
    }
}