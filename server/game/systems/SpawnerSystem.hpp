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
    bool _gameJustStarted = true;
    void spawnRandom(const std::shared_ptr<Engine::Entity> &spawner, std::vector<std::string> &enemies);
    void handleMove(std::shared_ptr<Engine::Entity> &spawner);
    void handleSpawn(std::shared_ptr<Engine::Entity> &spawner);
    void handleWaves(std::shared_ptr<Engine::Entity> &spawner);
public:
    explicit SpawnerSystem(std::shared_ptr<Game> &game);
    void update() override;

    void spawnEnemy(const std::shared_ptr<Engine::Entity> &spawner, std::string enemy);
};


#endif //RTYPE_SPAWNERSYSTEM_HPP
