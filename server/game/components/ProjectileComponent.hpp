//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_PROJECTILECOMPONENT_HPP
#define RTYPE_PROJECTILECOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"

class ProjectileComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _birth;
    double _damage;
    double _lifetime;

public:
    explicit ProjectileComponent() : _damage(0), _lifetime(0), Engine::Component() {}
    explicit ProjectileComponent(double damage, double lifetime) : _damage(damage), _lifetime(lifetime),
    _birth(std::chrono::high_resolution_clock::now()), Engine::Component() {}

    [[nodiscard]] double getDamage() const {return _damage;}
    void setDamage(double damage) {_damage = damage;}

    [[nodiscard]] double getLifetime() const {return _lifetime;}
    void setLifetime(double lifetime) {_lifetime = lifetime;}

    [[nodiscard]] bool isLifetimeOver() const {return Engine::Timer::hasElapsed(_birth, _lifetime);}
};

#endif //RTYPE_PROJECTILECOMPONENT_HPP