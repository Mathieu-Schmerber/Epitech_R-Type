/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ENEMYSYSTEM_HPP
#define RTYPE_ENEMYSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Enemy.hpp"
#include "Game.hpp"

class EnemySystem : public Engine::System {
private:
    std::shared_ptr<Game> _game;

public:
    explicit EnemySystem(std::shared_ptr<Game> &game);
    void handleMovements(std::shared_ptr<Engine::Entity> &enemy);
    bool didCollide(std::shared_ptr<Engine::Entity> &enemy);

    void deleteEntity(std::shared_ptr<Engine::Entity> &entity) override;

    void update() override;
};

#endif //RTYPE_ENEMYSYSTEM_HPP
