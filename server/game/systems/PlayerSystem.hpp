//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_PLAYERSYSTEM_HPP
#define RTYPE_PLAYERSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Player.hpp"
#include "Game.hpp"

class PlayerSystem : public Engine::System
{
private:
    std::shared_ptr<Game> _game;
    std::shared_ptr<Engine::ATexture> _projectileTexture;

    static void handleMoveAnimations(std::shared_ptr<Engine::Entity> &player, Engine::Vector<double> dir);
    static void handleMovements(std::shared_ptr<Engine::Entity> &player);
    void handleWeapon(std::shared_ptr<Engine::Entity> &player);
    static void handleCollisions(std::shared_ptr<Engine::Entity> &player);
public:
    explicit PlayerSystem(std::shared_ptr<Game> &game);

    void update() override;
};

#endif //RTYPE_PLAYERSYSTEM_HPP