//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_AUTOMATICWEAPONCOMPONENT_HPP
#define RTYPE_AUTOMATICWEAPONCOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"

class AutomaticWeaponComponent : public Engine::Component
{
private:
    double _cooldown = 2;
    std::chrono::high_resolution_clock::time_point _lastShoot = std::chrono::high_resolution_clock::now();

    double _baseDamage;
    double _damageMultiplier;
    double _shotSpeed = -30;

public:
    explicit AutomaticWeaponComponent() : _baseDamage(0), _damageMultiplier(0), _cooldown(0),
    _lastShoot(std::chrono::high_resolution_clock::now()), Engine::Component() {}
    explicit AutomaticWeaponComponent(double damage, double multiplier, double cooldown, double shotSpeed)
    : _baseDamage(damage), _damageMultiplier(multiplier), _cooldown(cooldown), _lastShoot(std::chrono::high_resolution_clock::now())
    , _shotSpeed(shotSpeed), Engine::Component() {}

    [[nodiscard]] double getCurrentDamages() const {return (this->_baseDamage + (_baseDamage * _damageMultiplier));}
    [[nodiscard]] bool canShoot() const {return Engine::Timer::hasElapsed(_lastShoot, _cooldown);}
    void refreshShoots() {_lastShoot = std::chrono::high_resolution_clock::now();}
    [[nodiscard]] double getShotSpeed() {return _shotSpeed;}
};

#endif //RTYPE_AUTOMATICWEAPONCOMPONENT_HPP
