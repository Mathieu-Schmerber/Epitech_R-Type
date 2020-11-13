//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_MANUALWEAPONCOMPONENT_HPP
#define RTYPE_MANUALWEAPONCOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"

class ManualWeaponComponent : public Engine::Component
{
private:
    double _cooldown;
    double _maxChargeTime;
    bool _charging = false;
    std::chrono::high_resolution_clock::time_point _startCharge;
    std::chrono::high_resolution_clock::time_point _lastShoot;
    char _upgrade = 0;
    char _maxUpgrade = 3;
    double _baseDamage;
    double _damageMultiplier;

public:
    explicit ManualWeaponComponent() : _baseDamage(0), _damageMultiplier(0), _cooldown(0), _maxChargeTime(2000),
                                       _lastShoot(std::chrono::high_resolution_clock::now()), Engine::Component() {}
    explicit ManualWeaponComponent(double damage, double multiplier, double cooldown)
    : _baseDamage(damage), _damageMultiplier(multiplier), _cooldown(cooldown), _maxChargeTime(2000), _lastShoot(std::chrono::high_resolution_clock::now())
    , Engine::Component() {}

    [[nodiscard]] double getMaxChargeTime() const {return _maxChargeTime;}
    [[nodiscard]] const std::chrono::high_resolution_clock::time_point &getStartCharge() const {return _startCharge;}
    void beginCharge() {
        _startCharge = std::chrono::high_resolution_clock::now();
        _charging = true;
    }
    void abortCharge() {
        _startCharge = std::chrono::high_resolution_clock::now();
        this->_charging = false;
    }
    [[nodiscard]] bool isCharging() const {return this->_charging;}

    void upgrade() {if (this->_upgrade < this->_maxUpgrade) this->_upgrade++;}

    [[nodiscard]] double getCurrentDamages() const {return (this->_baseDamage + (_baseDamage * _damageMultiplier * _upgrade));}
    [[nodiscard]] bool canShoot() const {return Engine::Timer::hasElapsed(_lastShoot, _cooldown);}
    void refreshShoots() {_lastShoot = std::chrono::high_resolution_clock::now();}
};

#endif //RTYPE_MANUALWEAPONCOMPONENT_HPP
