//
// Created by mathi on 01/11/2020.
//

#include "systems/MouseSystem.hpp"
#include "components/ColliderComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/SpriteComponent.hpp"

Engine::MouseSystem::MouseSystem(std::shared_ptr<Engine::AEvents> &events) : _events(events), Engine::System()
{
    this->addDependency<ColliderComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::MouseSystem::update()
{
    bool released = !this->_events->getButtonsReleased().empty();
    bool pressed = !this->_events->getButtonsPressed().empty();
    Point<int> mousePos = this->_events->getMousePosWindowRelative();

    for (auto &e : this->_entities) {
        auto collider = e->getComponent<ColliderComponent>();
        auto clickable = e->getComponent<ClickableComponent>();
        if (e->getComponent<SpriteComponent>()&& !e->getComponent<SpriteComponent>()->isVisible())
            continue;
        clickable->setIsReleased(released && Geometry::doOverlap({(float)mousePos.x, (float)mousePos.y}, collider->getHitBox()));
        clickable->setIsClicked(pressed && Geometry::doOverlap({(float)mousePos.x, (float)mousePos.y}, collider->getHitBox()));
        clickable->setIsHover(Geometry::doOverlap({(float)mousePos.x, (float)mousePos.y}, collider->getHitBox()));
    }
}