//
// Created by mathi on 01/11/2020.
//

#include "systems/MouseSystem.hpp"
#include "components/ColliderComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "enumerations/ButtonState.hpp"

Engine::MouseSystem::MouseSystem(std::shared_ptr<Engine::AEvents> &events) : _events(events), Engine::System()
{
    this->addDependency<ColliderComponent>();
    this->addDependency<ClickableComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::MouseSystem::update()
{
    bool released = !this->_events->getButtonsReleased().empty();
    bool pressed = !this->_events->getButtonsPressed().empty();
    Point<int> mousePos = this->_events->getMousePosWindowRelative();
    ColliderComponent *collider = nullptr;
    ClickableComponent *clickable = nullptr;
    AnimationComponent *animation = nullptr;

    for (auto &e : this->_entities) {
        collider = e->getComponent<ColliderComponent>();
        clickable = e->getComponent<ClickableComponent>();
        animation = e->getComponent<AnimationComponent>();
        if (!e->getComponent<SpriteComponent>()->isVisible())
            continue;
        else if (released && Geometry::doOverlap({(double)mousePos.x, (double)mousePos.y}, collider->getHitBox()))
            clickable->onClick();
        if (animation) {
            if (pressed && Geometry::doOverlap({(double)mousePos.x, (double)mousePos.y}, collider->getHitBox()))
                animation->setAnimation(ButtonState::CLICKED);
            else if (Geometry::doOverlap({(double)mousePos.x, (double)mousePos.y}, collider->getHitBox()))
                animation->setAnimation(ButtonState::HOVER);
            else
                animation->setAnimation(ButtonState::IDLE);
        }
    }
}