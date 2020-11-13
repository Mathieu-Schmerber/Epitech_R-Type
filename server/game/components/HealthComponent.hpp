/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_HEALTHCOMPONENT_HPP
#define RTYPE_HEALTHCOMPONENT_HPP

#include "ecs/Component.hpp"

class HealthComponent : public Engine::Component {
private:
    double _maxHealth = 100;
    double _currentHealth = 100;

public:
    explicit HealthComponent() = default;
    explicit HealthComponent(double maxHealth, double currentHealth) : _maxHealth(maxHealth), _currentHealth(currentHealth), Engine::Component() {}
    explicit HealthComponent(double maxHealth) : _maxHealth(maxHealth), _currentHealth(maxHealth), Engine::Component() {}

    void setMaxHealth(double maxHealth) {_maxHealth = maxHealth;}
    void setCurrentHealth(double currentHealth) {_currentHealth = currentHealth;}
    void loseHealth(double healthLost) {_currentHealth = _currentHealth - healthLost >= 0 ? _currentHealth - healthLost : 0;}
    void gainHealth(double gainHealth) {_currentHealth = _currentHealth + gainHealth <= _maxHealth ? _currentHealth + gainHealth : _maxHealth;}

    [[nodiscard]] double getMaxHealth() const {return _maxHealth;}
    [[nodiscard]] double getCurrentHealth() const {return _currentHealth;}
};


#endif //RTYPE_HEALTHCOMPONENT_HPP
