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
    float _cooldown;
    std::chrono::high_resolution_clock::time_point _lastShoot;
    char _upgrade = 0;
    char _maxUpgrade = 3;
    float _baseDamage;
    float _damageMultiplier;

public:
    explicit AutomaticWeaponComponent() : _baseDamage(0), _damageMultiplier(0), _cooldown(0),
    _lastShoot(std::chrono::high_resolution_clock::now()), Engine::Component() {}
    explicit AutomaticWeaponComponent(float damage, float multiplier, float cooldown)
    : _baseDamage(damage), _damageMultiplier(multiplier), _cooldown(cooldown), _lastShoot(std::chrono::high_resolution_clock::now())
    , Engine::Component() {}

    void upgrade() {if (this->_upgrade < this->_maxUpgrade) this->_upgrade++;}

    [[nodiscard]] float getCurrentDamages() const {return (this->_baseDamage + (_baseDamage * _damageMultiplier * _upgrade));}
    [[nodiscard]] bool canShoot() const {return Engine::Timer::hasElapsed(_lastShoot, _cooldown);}
    void refreshShoots() {_lastShoot = std::chrono::high_resolution_clock::now();}
};

#endif //RTYPE_AUTOMATICWEAPONCOMPONENT_HPP
