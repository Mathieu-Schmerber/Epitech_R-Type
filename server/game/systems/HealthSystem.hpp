/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_HEALTHSYSTEM_HPP
#define RTYPE_HEALTHSYSTEM_HPP

#include "ecs/System.hpp"
#include "Game.hpp"

class HealthSystem : public Engine::System {
private:
    std::shared_ptr<Game> _game;
public:
    explicit HealthSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_HEALTHSYSTEM_HPP
