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
    double _damage;

public:
    explicit ProjectileComponent() : _damage(0), Engine::Component() {}
    explicit ProjectileComponent(double damage) : _damage(damage), Engine::Component() {}

    [[nodiscard]] double getDamage() const {return _damage;}
    void setDamage(double damage) {_damage = damage;}
};

#endif //RTYPE_PROJECTILECOMPONENT_HPP