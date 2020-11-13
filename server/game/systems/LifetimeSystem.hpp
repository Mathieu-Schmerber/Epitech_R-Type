//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_LIFETIMESYSTEM_HPP
#define RTYPE_LIFETIMESYSTEM_HPP

#include "Game.hpp"
#include "ecs/System.hpp"

class LifetimeSystem : public Engine::System
{
private:
    std::shared_ptr<Game> _game;

public:
    explicit LifetimeSystem(std::shared_ptr<Game> &game);

    void update() override;
};

#endif //RTYPE_LIFETIMESYSTEM_HPP
