//
// Created by mathi on 09/11/2020.
//

#include "systems/ButtonSystem.hpp"
#include "components/ButtonComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/AnimationComponent.hpp"

Engine::ButtonSystem::ButtonSystem()
{
    this->addDependency<ButtonComponent>();
    this->addDependency<ClickableComponent>();
    this->addDependency<AnimationComponent>();
}

void Engine::ButtonSystem::update()
{
    ButtonComponent *btn = nullptr;
    ClickableComponent *clickable = nullptr;
    AnimationComponent *anim = nullptr;

    for (auto &e : this->_entities) {
        btn = e->getComponent<ButtonComponent>();
        clickable = e->getComponent<ClickableComponent>();
        anim = e->getComponent<AnimationComponent>();
        if (clickable->isReleased())
            btn->onClick();
        else if (clickable->isClicked())
            anim->setAnimation(ButtonComponent::ButtonState::CLICKED);
        else if (clickable->isHover())
            anim->setAnimation(ButtonComponent::ButtonState::HOVER);
        else
            anim->setAnimation(ButtonComponent::ButtonState::IDLE);
    }
}