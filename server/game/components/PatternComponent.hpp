/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_PATTERNCOMPONENT_HPP
#define RTYPE_PATTERNCOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include <memory>

class PatternComponent : public Engine::Component
{
private:
    void (*_patternMove)(std::shared_ptr<Engine::Entity> &);

public:
    explicit PatternComponent() : _patternMove(nullptr), Engine::Component() {}
    explicit PatternComponent(void (*patternMove)(std::shared_ptr<Engine::Entity> &)) : _patternMove(patternMove), Engine::Component() {}

    void move(std::shared_ptr<Engine::Entity> &entity) {
        (*_patternMove)(entity);
    }
};

#endif //RTYPE_PATTERNCOMPONENT_HPP
