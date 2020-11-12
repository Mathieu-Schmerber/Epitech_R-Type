//
// Created by mathi on 02/11/2020.
//

#include "systems/AnimationSystem.hpp"
#include "components/AnimationComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "tools/Timer.hpp"

Engine::AnimationSystem::AnimationSystem() : Engine::System()
{
    this->addDependency<SpriteComponent>();
    this->addDependency<AnimationComponent>();
}

void Engine::AnimationSystem::update()
{
    for (auto &e : this->_entities) {
        auto sprite = e->getComponent<SpriteComponent>();
        auto animation = e->getComponent<AnimationComponent>();
        if (animation->hasAnimations() && Engine::Timer::hasElapsed(animation->getLastRefresh(), animation->getFrameTime())) {
            sprite->getSprite()->setRect(animation->getNextFrame());
            animation->refresh();
        }
    }
}