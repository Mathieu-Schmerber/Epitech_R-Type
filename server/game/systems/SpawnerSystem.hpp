/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SPAWNERSYSTEM_HPP
#define RTYPE_SPAWNERSYSTEM_HPP

#ifdef __unix__
#define DLL_PATH "../lib/libfloatingRobot.so"
#elif defined(_WIN32) || defined(WIN32)
#define DLL_PATH "./floatingRobot.dll"
#endif

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
