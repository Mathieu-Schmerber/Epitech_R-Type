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
    std::map<ProjectileComponent::Type, std::shared_ptr<Engine::ATexture>> _textures = {
            {ProjectileComponent::Type::BASIC, std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_1_72x18_18x18.png")},
            {ProjectileComponent::Type::BEAM, std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_2_102x34_34x34.png")},
            {ProjectileComponent::Type::SHURIKEN, std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_3_200x18_50x18.png")}
    };
    std::map<ProjectileComponent::Type, std::vector<Engine::Box<double>>> _anims = {
            {ProjectileComponent::Type::BASIC, {
                {{18 * 0, 0}, {18, 18}},
                {{18 * 1, 0}, {18, 18}},
                {{18 * 2, 0}, {18, 18}}}},
            {ProjectileComponent::Type::BEAM, {
                {{34 * 0, 0}, {34, 34}},
                {{34 * 1, 0}, {34, 34}},
                {{34 * 2, 0}, {34, 34}}}},
            {ProjectileComponent::Type::SHURIKEN, {
                {{50 * 0, 0}, {50, 18}},
                {{50 * 1, 0}, {50, 18}},
                {{50 * 2, 0}, {50, 18}}}},
    };

    std::shared_ptr<Game> _game;
    std::shared_ptr<Engine::ATexture> _projectileTexture;

    std::shared_ptr<Engine::Entity> generateProjectile(AutomaticWeaponComponent *weapon);
    void automaticShot(std::shared_ptr<Engine::Entity> &shooter);
    bool hasToShoot(AutomaticWeaponComponent *weapon);
    void targetShoot(Engine::VelocityComponent *velocity, Engine::TargetComponent *target, Engine::Vector<double> pos, AutomaticWeaponComponent *weapon);
public:
    explicit AutomaticWeaponSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_AUTOMATICWEAPONSYSTEM_HPP
