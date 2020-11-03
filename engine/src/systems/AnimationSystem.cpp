//
// Created by mathi on 02/11/2020.
//

#include "systems/AnimationSystem.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "Timer.hpp"

Engine::AnimationSystem::AnimationSystem() : Engine::System()
{
    this->addDependency<SpriteComponent>();
    this->addDependency<AnimationComponent>();
}

void Engine::AnimationSystem::update()
{
    SpriteComponent *sprite = nullptr;
    AnimationComponent *animation = nullptr;

    for (auto &e : this->_entities) {
        sprite = e->getComponent<SpriteComponent>();
        animation = e->getComponent<AnimationComponent>();
        if (animation->hasAnimations() && Engine::Timer::hasElapsed(animation->getLastRefresh(), animation->getFrameTime())) {
            sprite->getSprite()->setRect(animation->getNextFrame());
            animation->refresh();
        }
    }
}