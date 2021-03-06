/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SPAWNERSYSTEM_HPP
#define RTYPE_SPAWNERSYSTEM_HPP

#include "ecs/System.hpp"
#include "dataHolders/DataMusic.hpp"
#include "entities/Spawner.hpp"
#include "Game.hpp"

class SpawnerSystem : public Engine::System {
private:
    std::vector<std::string> _musics;
    std::shared_ptr<Game> _game;
    bool _gameJustStarted = true;
    void spawnRandom(const std::shared_ptr<Engine::Entity> &spawner, std::vector<std::string> &enemies);
    void handleMove(std::shared_ptr<Engine::Entity> &spawner);
    void handleSpawn(std::shared_ptr<Engine::Entity> &spawner);
    void handleWaves(std::shared_ptr<Engine::Entity> &spawner);
    std::shared_ptr<Engine::Entity> _boss = nullptr;
public:
    explicit SpawnerSystem(std::shared_ptr<Game> &game);
    void update() override;

    void spawnEnemy(const std::shared_ptr<Engine::Entity> &spawner, std::string enemy, bool boss);

};


#endif //RTYPE_SPAWNERSYSTEM_HPP
