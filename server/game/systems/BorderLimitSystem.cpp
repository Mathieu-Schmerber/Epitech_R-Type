//
// Created by mathi on 15/11/2020.
//

#include "BorderLimitSystem.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"

BorderLimitSystem::BorderLimitSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::NetworkComponent>();
    this->addDependency<Engine::SpriteComponent>();
}

void BorderLimitSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (e->getComponent<Engine::TransformComponent>()->getPos().x < -e->getComponent<Engine::SpriteComponent>()->getSprite()->getRect().size.x * 2)
            _game->despawn(e);
    }
}