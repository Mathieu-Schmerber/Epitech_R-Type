/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "components/TextComponent.hpp"
#include "entities/Ground.hpp"
#include "components/EnemySpawnerComponent.hpp"
#include "SpawnerSystem.hpp"
#include "components/ColliderComponent.hpp"
#include "tools/RandomETU.hpp"
#include "components/WaveComponent.hpp"

SpawnerSystem::SpawnerSystem(std::shared_ptr<Game> &game) : _game(game)
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<EnemySpawnerComponent>();
    this->_musics = {
            STAGE_1,
            STAGE_2,
            STAGE_3,
            STAGE_4,
            WIN,
    };
}

void SpawnerSystem::handleSpawn(std::shared_ptr<Engine::Entity> &spawner)
{
    if (spawner->getComponent<EnemySpawnerComponent>()->canSpawn()) {
        auto enemies = spawner->getComponent<EnemySpawnerComponent>()->getLibs();
        try {
            spawnRandom(spawner, enemies);
        } catch (Engine::EngineException &e) {
            std::cerr << e << std::endl;
            throw Engine::SystemError("SpawnerSystem: Unable to spawn new entity");
        }
    }
}

void SpawnerSystem::spawnRandom(const std::shared_ptr<Engine::Entity> &spawner, std::vector<std::string> &enemies)
{
    std::shared_ptr<Enemy> e = std::shared_ptr<Enemy>(spawner->getComponent<EnemySpawnerComponent>()->getEntity(
            enemies.at(Engine::RandomETU::randETU(static_cast<int>(enemies.size()) - 1))));
    e->getComponent<Engine::TransformComponent>()->setPos(spawner->getComponent<Engine::TransformComponent>()->getPos());
    if (e->getComponent<Engine::TargetComponent>())
        e->getComponent<Engine::TargetComponent>()->addTargets(_game->getPlayersSpaceShips());
    _game->spawn(e, true);
}

void SpawnerSystem::spawnEnemy(const std::shared_ptr<Engine::Entity> &spawner, std::string enemy)
{
    std::shared_ptr<Enemy> e = std::shared_ptr<Enemy>(spawner->getComponent<EnemySpawnerComponent>()->getEntity(enemy));
    e->getComponent<Engine::TransformComponent>()->setPos(spawner->getComponent<Engine::TransformComponent>()->getPos());
    if (e->getComponent<Engine::TargetComponent>())
        e->getComponent<Engine::TargetComponent>()->addTargets(_game->getPlayersSpaceShips());
    _game->spawn(e, true);
}

void SpawnerSystem::handleMove(std::shared_ptr<Engine::Entity> &spawner)
{
    if (spawner->getComponent<Engine::TransformComponent>()->getPos().y >= 1080 - (GROUND_HEIGHT * 4) ||
    spawner->getComponent<Engine::TransformComponent>()->getPos().y <= (GROUND_HEIGHT * 4)) {
        spawner->getComponent<Engine::VelocityComponent>()->setSpeed(spawner->getComponent<Engine::VelocityComponent>()->getSpeed() * Engine::Vector<double>({0, -1}));
    }
}

void SpawnerSystem::handleWaves(std::shared_ptr<Engine::Entity> &spawner)
{
    auto wave = spawner->getComponent<WaveComponent>();
    auto transform = spawner->getComponent<Engine::TransformComponent>();
    auto text = spawner->getComponent<Engine::TextComponent>();
    auto music = spawner->getComponent<Engine::MusicComponent>();

    if (_gameJustStarted) {
        _gameJustStarted = false;
        text->setHasToBeDraw(true);
        text->getText()->setString(wave->getTextFromWave(wave->getCurrentWave()));
        text->setHasToBeDraw(true);

        auto newMusic = std::make_unique<DataMusic>(_musics[wave->getCurrentWave()]);
        music->setMusic(std::move(newMusic));
        music->playMe(true);

    }
    if (wave->timeToSwitch()) {
        wave->goNextScene();

        auto newMusic = std::make_unique<DataMusic>(_musics[wave->getCurrentWave()]);
        music->setMusic(std::move(newMusic));
        music->playMe(true);

        spawner->getComponent<EnemySpawnerComponent>()->setSpawnRate(spawner->getComponent<EnemySpawnerComponent>()->getSpawnRate() + 4);
        if (wave->getCurrentWave() != WaveComponent::victory)
            spawner->getComponent<EnemySpawnerComponent>()->setSpawnRate(spawner->getComponent<EnemySpawnerComponent>()->getSpawnRate() + 4);
        else
            spawner->getComponent<EnemySpawnerComponent>()->setSpawnRate(0);
        text->getText()->setString(wave->getTextFromWave(wave->getCurrentWave()));
        text->getText()->setFillColor(Engine::Color({0, 0, 0, 255}));
        text->setHasToBeDraw(true);
    }
    auto textDuration = 2.3;
    if (wave->getElapsedSecondSinceLastStart() < textDuration) {
        int alpha = static_cast<int>(wave->getElapsedSecondSinceLastStart() * 255 / textDuration);
        auto c = static_cast<unsigned char>(255 - alpha);
        text->getText()->setFillColor(Engine::Color({0, 0, 0, c}));
    } else {
        text->setHasToBeDraw(false);
    }
    if (wave->getCurrentWave() == WaveComponent::boss && wave->getElapsedSecondSinceLastStart() < wave->getDurationFromWave(WaveComponent::boss)) {
        if (Engine::RandomETU::randETU(60) == Engine::RandomETU::randETU(60))
        spawnEnemy(spawner, FLAPPING_ROBOT);
    }
    if (wave->getCurrentWave() == WaveComponent::victory)  {
        std::cout << wave->getElapsedSecondSinceLastStart() << " " << wave->getDurationFromWave(WaveComponent::victory) << std::endl;
    }
    if (wave->getCurrentWave() == WaveComponent::victory && wave->getElapsedSecondSinceLastStart() > wave->getDurationFromWave(WaveComponent::victory)) {
        _game->stopTheGame();
    }
}

void SpawnerSystem::update()
{
    for (auto &e : _entities) {
        try {
            handleSpawn(e);
        } catch (Engine::EngineException &e) {
            std::cerr << e << std::endl;
        }
        handleMove(e);
        handleWaves(e);
    }
}
