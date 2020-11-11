//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_PROJECTILESYSTEM_HPP
#define RTYPE_PROJECTILESYSTEM_HPP

#include "Game.hpp"
#include "ecs/System.hpp"

class ProjectileSystem : public Engine::System
{
private:
    std::shared_ptr<Game> _game;
public:
    explicit ProjectileSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_PROJECTILESYSTEM_HPP
