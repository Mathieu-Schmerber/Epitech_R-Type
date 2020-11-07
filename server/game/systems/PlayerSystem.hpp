//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_PLAYERSYSTEM_HPP
#define RTYPE_PLAYERSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Player.hpp"

class PlayerSystem : public Engine::System
{
private:
    static void handleMovements(std::shared_ptr<Engine::Entity> &player);
    static void handleWeapon(std::shared_ptr<Engine::Entity> &player);
    static void handleCollisions(std::shared_ptr<Engine::Entity> &player);
public:
    PlayerSystem();

    void update() override;
};

#endif //RTYPE_PLAYERSYSTEM_HPP