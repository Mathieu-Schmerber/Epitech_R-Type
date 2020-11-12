//
// Created by mathi on 12/11/2020.
//

#ifndef RTYPE_GROUNDSYSTEM_HPP
#define RTYPE_GROUNDSYSTEM_HPP

#include "ecs/System.hpp"
#include "Game.hpp"
#include "entities/Ground.hpp"

class GroundSystem : public Engine::System
{
private:
    std::vector<std::shared_ptr<Engine::Entity>> _grounds;
    std::shared_ptr<Game> _game;
    std::vector<int> _graph;
    int _lastHeight;

    void spawnGrounds(int xOffset, int yOffset);

public:
    explicit GroundSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_GROUNDSYSTEM_HPP
