//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_PROJECTILECOMPONENT_HPP
#define RTYPE_PROJECTILECOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"

class ProjectileComponent : public Engine::Component
{
public:
    enum Type {BASIC, BEAM, BOUNDS};

    explicit ProjectileComponent() : _damage(0), _nbHit(0), Engine::Component() {}
    explicit ProjectileComponent(double damage) : _damage(damage), _nbHit(1), Engine::Component() {}

    [[nodiscard]] double getDamage() const {return _damage;}
    void setDamage(double damage) {_damage = damage;}

    [[nodiscard]] const std::vector<std::shared_ptr<Engine::Entity>> &getHit() const {
        return _hit;
    }

    void addHit(const std::shared_ptr<Engine::Entity> &hit) {
        _hit.push_back(hit);
    }

    [[nodiscard]] int getNbHit() const {
        return _nbHit;
    }

    void setNbHit(int nbHit) {
        _nbHit = nbHit;
    }

private:
    int _nbHit;
    double _damage;
    std::vector<std::shared_ptr<Engine::Entity>> _hit;
};

#endif //RTYPE_PROJECTILECOMPONENT_HPP