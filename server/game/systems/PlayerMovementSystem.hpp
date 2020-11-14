//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_PLAYERMOVEMENTSYSTEM_HPP
#define RTYPE_PLAYERMOVEMENTSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Player.hpp"
#include "components/CollectibleComponent.hpp"
#include "Game.hpp"

class PlayerMovementSystem : public Engine::System
{
private:
    [[nodiscard]] static bool willExitScreen(Engine::Point<double> pos, Engine::Vector<double> dir);
    static void handleMoveAnimations(std::shared_ptr<Engine::Entity> &player, Engine::Vector<double> dir);
    static void handleMovements(std::shared_ptr<Engine::Entity> &player);

public:
    explicit PlayerMovementSystem();

    void update() override;
};

#endif //RTYPE_PLAYERMOVEMENTSYSTEM_HPP