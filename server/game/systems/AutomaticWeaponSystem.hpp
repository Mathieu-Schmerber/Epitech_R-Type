/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AUTOMATICWEAPONSYSTEM_HPP
#define RTYPE_AUTOMATICWEAPONSYSTEM_HPP

#include "ecs/System.hpp"
#include "components/AutomaticWeaponComponent.hpp"
#include "Game.hpp"

class AutomaticWeaponSystem : public Engine::System {
private:
    std::shared_ptr<Game> _game;
    std::shared_ptr<Engine::ATexture> _projectileTexture;

    void automaticShot(std::shared_ptr<Engine::Entity> &shooter);
    bool hasToShoot(AutomaticWeaponComponent *weapon);
public:
    explicit AutomaticWeaponSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_AUTOMATICWEAPONSYSTEM_HPP
