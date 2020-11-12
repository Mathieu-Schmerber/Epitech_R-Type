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
    float _damage;
    float _lifetime;

public:
    explicit ProjectileComponent() : _damage(0), _lifetime(0), Engine::Component() {}
    explicit ProjectileComponent(float damage, float lifetime) : _damage(damage), _lifetime(lifetime),
    _birth(std::chrono::high_resolution_clock::now()), Engine::Component() {}

    [[nodiscard]] float getDamage() const {return _damage;}
    void setDamage(float damage) {_damage = damage;}

    [[nodiscard]] float getLifetime() const {return _lifetime;}
    void setLifetime(float lifetime) {_lifetime = lifetime;}

    [[nodiscard]] bool isLifetimeOver() const {return Engine::Timer::hasElapsed(_birth, _lifetime);}
};

#endif //RTYPE_PROJECTILECOMPONENT_HPP