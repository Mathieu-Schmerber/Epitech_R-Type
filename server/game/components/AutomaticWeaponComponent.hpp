//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_AUTOMATICWEAPONCOMPONENT_HPP
#define RTYPE_AUTOMATICWEAPONCOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"
#include "components/ProjectileComponent.hpp"
#include "CollisionMasks.hpp"

class AutomaticWeaponComponent : public Engine::Component
{
private:
    Collision::Mask _projectileMask;
    double _cooldown = 2;
    std::chrono::high_resolution_clock::time_point _lastShoot = std::chrono::high_resolution_clock::now();

    double _baseDamage;
    double _damageMultiplier;
    Engine::Vector<double> _shotSpeed = {-30, 0};

    ProjectileComponent::Type _projectileType;
    bool _bounce = false;

public:

    explicit AutomaticWeaponComponent() : _baseDamage(0), _damageMultiplier(0), _cooldown(0), _projectileMask(Collision::Mask::ENEMY_PROJECTILE),
                                          _projectileType(ProjectileComponent::Type::BASIC), _lastShoot(std::chrono::high_resolution_clock::now()), Engine::Component() {}
    explicit AutomaticWeaponComponent(double damage, double multiplier, double cooldown, Engine::Vector<double> shotSpeed, Collision::Mask mask, ProjectileComponent::Type type)
    : _baseDamage(damage), _damageMultiplier(multiplier), _cooldown(cooldown), _lastShoot(std::chrono::high_resolution_clock::now()), _projectileMask(mask),
    _projectileType(type), _shotSpeed(shotSpeed), Engine::Component() {}

    [[nodiscard]] double getCurrentDamages() const {return (this->_baseDamage + (_baseDamage * _damageMultiplier));}
    [[nodiscard]] bool canShoot() const {return Engine::Timer::hasElapsed(_lastShoot, _cooldown);}
    void refreshShoots() {_lastShoot = std::chrono::high_resolution_clock::now();}
    [[nodiscard]] Engine::Vector<double> getShotSpeed() const {return _shotSpeed;}
    [[nodiscard]] Collision::Mask getProjectileMask() const {return _projectileMask;}
    void setProjectileMask(Collision::Mask projectileMask) {_projectileMask = projectileMask;}
    [[nodiscard]] ProjectileComponent::Type getProjectileType() const {return _projectileType;}
    [[nodiscard]] bool canBounce() const {return _bounce;}
    void setBounce(bool bounce) {_bounce = bounce;}
};

#endif //RTYPE_AUTOMATICWEAPONCOMPONENT_HPP
