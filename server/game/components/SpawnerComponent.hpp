/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SPAWNERCOMPONENT_HPP
#define RTYPE_SPAWNERCOMPONENT_HPP

#include <chrono>
#include <tools/Timer.hpp>
#include "ecs/Component.hpp"

class SpawnerComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _timeSinceLastSpawn = std::chrono::high_resolution_clock::now();
    double _spawnRate = 5;
    double _scale = 30; // 30s

public:
    explicit SpawnerComponent() : Engine::Component() {}
    explicit SpawnerComponent(double spawnRate) : _spawnRate(spawnRate), Engine::Component() {}

    void setSpawnRate(double spawnRate) {_spawnRate = spawnRate;}
    [[nodiscard]] bool canSpawn() const {return Engine::Timer::hasElapsed(_timeSinceLastSpawn, _scale / _spawnRate);}
    void spawn() {_timeSinceLastSpawn = std::chrono::high_resolution_clock::now();}
};

#endif //RTYPE_SPAWNERCOMPONENT_HPP
