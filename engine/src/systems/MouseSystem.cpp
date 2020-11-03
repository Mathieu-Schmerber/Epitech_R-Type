//
// Created by mathi on 01/11/2020.
//

#include "systems/MouseSystem.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "enumerations/ButtonState.hpp"

Engine::MouseSystem::MouseSystem(std::shared_ptr<Engine::AEvents> &events) : _events(events), Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::MouseSystem::update()
{
    bool released = !this->_events->getButtonsReleased().empty();
    bool pressed = !this->_events->getButtonsPressed().empty();
    Point<int> mousePos = this->_events->getMousePosWindowRelative();
    Box<int> box(0, 0, 0, 0);
    TransformComponent *transform = nullptr;
    SpriteComponent *sprite = nullptr;
    ClickableComponent *clickable = nullptr;
    AnimationComponent *animation = nullptr;

    for (auto &e : this->_entities) {
        transform = e->getComponent<TransformComponent>();
        sprite = e->getComponent<SpriteComponent>();
        clickable = e->getComponent<ClickableComponent>();
        animation = e->getComponent<AnimationComponent>();
        box = Box<int>(transform->getPos(), sprite->getSprite()->getSize());
        if (released && Geometry::doOverlap(mousePos, box))
            clickable->onClick();
        if (animation) {
            if (pressed && Geometry::doOverlap(mousePos, box))
                animation->setAnimation(ButtonState::CLICKED);
            else if (Geometry::doOverlap(mousePos, box))
                animation->setAnimation(ButtonState::HOVER);
            else
                animation->setAnimation(ButtonState::IDLE);
        }
    }
}