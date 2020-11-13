//
// Created by mathi on 12/11/2020.
//

#ifndef RTYPE_COLLISIONMASKS_HPP
#define RTYPE_COLLISIONMASKS_HPP

#include "ecs/Entity.hpp"
#include "components/ColliderComponent.hpp"
#include "tools/Utils.hpp"

namespace Collision {

    enum Mask {
        PLAYER = 0,
        PLAYER_PROJECTILE = 1,
        ENEMY = 2,
        ENEMY_PROJECTILE = 3,
        WALL = 4
    };

    static std::map<Mask, std::vector<Mask>> ignoranceMap = {
            {PLAYER, {PLAYER_PROJECTILE}},
            {PLAYER_PROJECTILE, {PLAYER}},
            {ENEMY, {ENEMY_PROJECTILE, WALL}},
            {ENEMY_PROJECTILE, {ENEMY}},
    };

    static bool doCollide(Mask myMask, std::vector<std::shared_ptr<Engine::Entity>> &entities) {
        Engine::ColliderComponent *collider;

        if (!Engine::Utils::isInMap(ignoranceMap, myMask))
            return false;
        for (auto &e : entities) {
            collider = e->getComponent<Engine::ColliderComponent>();
            if (collider && !Engine::Utils::isInVector(ignoranceMap[myMask], static_cast<Mask>(collider->getCollisionMask())))
                return true;
        }
        return false;
    }

    static std::vector<std::shared_ptr<Engine::Entity>> removeIgnored(Mask myMask, const std::vector<std::shared_ptr<Engine::Entity>> &list)
    {
        auto res = list;
        Engine::ColliderComponent *collider;

        if (!Engine::Utils::isInMap(ignoranceMap, myMask))
            return res;
        for (auto &e : res) {
            collider = e->getComponent<Engine::ColliderComponent>();
            if (collider && Engine::Utils::isInVector(ignoranceMap[myMask], static_cast<Mask>(collider->getCollisionMask())))
                Engine::Utils::removeFromVector(res, e);
        }
        return res;
    }
}

#endif //RTYPE_COLLISIONMASKS_HPP
