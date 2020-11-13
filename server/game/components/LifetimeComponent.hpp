//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_LIFETIMECOMPONENT_HPP
#define RTYPE_LIFETIMECOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"

class LifetimeComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _birth;
    double _lifetime;

public:
    explicit LifetimeComponent() : _lifetime(0), Engine::Component() {}
    explicit LifetimeComponent(double lifetime) : _lifetime(lifetime), _birth(std::chrono::high_resolution_clock::now()), Engine::Component() {}

    [[nodiscard]] double getLifetime() const {return _lifetime;}
    void setLifetime(double lifetime) {_lifetime = lifetime;}

    [[nodiscard]] bool isLifetimeOver() const {return Engine::Timer::hasElapsed(_birth, _lifetime);}
};

#endif //RTYPE_LIFETIMECOMPONENT_HPP
