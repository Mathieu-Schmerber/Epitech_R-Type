/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ENEMYSPAWNERCOMPONENT_HPP
#define RTYPE_ENEMYSPAWNERCOMPONENT_HPP

#include <chrono>
#include "tools/Timer.hpp"
#include "tools/DynamicLibManager.hpp"
#include "entities/Enemy.hpp"
#include "tools/DLLoader.hpp"
#include "ecs/Component.hpp"

#ifdef __unix__
#define FLOATING_ROBOT "../lib/libfloatingRobot.so"
#define FLAPPING_ROBOT "../lib/libflappingRobot.so"
#define BW_ROBOT "../lib/libbwRobot.so"
#define BOSS "../lib/libboss.so"
#elif defined(_WIN32) || defined(WIN32)
#define FLOATING_ROBOT "./floatingRobot.dll"
#define FLAPPING_ROBOT "./flappingRobot.dll"
#define BW_ROBOT "./bwRobot.dll"
#define BOSS "./boss.dll"
#endif

class EnemySpawnerComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _timeSinceLastSpawn = std::chrono::high_resolution_clock::now();
    double _spawnRate = 5;
    double _scale = 30; // 30s
    Engine::DynamicLibManager _dynLM;
    std::vector<std::string> _enemiesLibs = {FLOATING_ROBOT, FLAPPING_ROBOT, BW_ROBOT};

public:
    explicit EnemySpawnerComponent() : Engine::Component() {}
    explicit EnemySpawnerComponent(double spawnRate) : _spawnRate(spawnRate), Engine::Component() {}

    void setSpawnRate(double spawnRate) {_spawnRate = spawnRate;}
    [[nodiscard]] double getSpawnRate() const {return _spawnRate;}
    [[nodiscard]] bool canSpawn() const {return Engine::Timer::hasElapsed(_timeSinceLastSpawn, _scale / _spawnRate);}
    Enemy *getEntity(std::string libName) {
        _timeSinceLastSpawn = std::chrono::high_resolution_clock::now();
        _dynLM.loadNewLib<Enemy>(libName);
        try {
            return _dynLM.getInstance<Enemy>(libName);
        } catch (Engine::EngineException &e) {
            std::cerr << e << std::endl;
            throw Engine::ComponentError("Unable to get new Enemy Instance");
        }
    }
    [[nodiscard]] std::vector<std::string> getLibs() const {return _enemiesLibs;}
};

#endif //RTYPE_ENEMYSPAWNERCOMPONENT_HPP