/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_FLAPPINGROBOT_HPP
#define RTYPE_FLAPPINGROBOT_HPP

#include "entities/Enemy.hpp"
#include "tools/RandomETU.hpp"

#define PATH "../../client/assets/images/enemies/ennemy_10_264x33_33x33.png"
#define SIZE_X 33
#define SIZE_Y 33

class FlappingRobot : public Enemy {
private:
    const Engine::Size<double> _size = {SIZE_X, SIZE_Y};

public:
    explicit FlappingRobot(const Engine::Point<double> &pos = {0, 0});
};

#endif //RTYPE_FLAPPINGROBOT_HPP
