/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_BOSS_HPP
#define RTYPE_BOSS_HPP

#include "entities/Enemy.hpp"
#include "tools/RandomETU.hpp"

#define PATH "../../client/assets/images/boss/boss_2_178x147_356x147.png"
#define SIZE_X 178
#define SIZE_Y 147

class Boss : public Enemy {
private:
    const Engine::Size<double> _size = {SIZE_X, SIZE_Y};

public:
    explicit Boss(const Engine::Point<double> &pos = {0, 0});
};

#endif //RTYPE_BOSS_HPP
