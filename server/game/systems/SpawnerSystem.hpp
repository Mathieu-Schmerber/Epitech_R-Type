/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SPAWNERSYSTEM_HPP
#define RTYPE_SPAWNERSYSTEM_HPP

#include "ecs/System.hpp"
#include "Game.hpp"

class SpawnerSystem : public Engine::System {
private:
    std::shared_ptr<Game> _game;
public:
    explicit SpawnerSystem(std::shared_ptr<Game> &game);
    void update() override;

    void handleSpawn(std::shared_ptr<Engine::Entity> &spawner);
};


#endif //RTYPE_SPAWNERSYSTEM_HPP
