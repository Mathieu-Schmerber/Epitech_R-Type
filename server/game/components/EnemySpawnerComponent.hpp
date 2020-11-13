/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ENEMYSPAWNERCOMPONENT_HPP
#define RTYPE_ENEMYSPAWNERCOMPONENT_HPP

#include <chrono>
#include <tools/Timer.hpp>
#include <DynamicLibManager.hpp>
#include "entities/Enemy.hpp"
#include "DLLoader.hpp"
#include "ecs/Component.hpp"

class EnemySpawnerComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _timeSinceLastSpawn = std::chrono::high_resolution_clock::now();
    double _spawnRate = 5;
    double _scale = 30; // 30s
    DynamicLibManager _dynLM;

public:
    explicit EnemySpawnerComponent() : Engine::Component() {}
    explicit EnemySpawnerComponent(double spawnRate) : _spawnRate(spawnRate), Engine::Component() {}

    void setSpawnRate(double spawnRate) {_spawnRate = spawnRate;}
    [[nodiscard]] bool canSpawn() const {return Engine::Timer::hasElapsed(_timeSinceLastSpawn, _scale / _spawnRate);}
    Enemy *getEntity(std::string libName) {
        _timeSinceLastSpawn = std::chrono::high_resolution_clock::now();
        _dynLM.loadNewLib<Enemy>(libName);
        return _dynLM.getInstance<Enemy>(libName);
    }
};

#endif //RTYPE_ENEMYSPAWNERCOMPONENT_HPP
