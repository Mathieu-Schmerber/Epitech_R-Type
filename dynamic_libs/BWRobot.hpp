/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_BWROBOT_HPP
#define RTYPE_BWROBOT_HPP

#include "entities/Enemy.hpp"
#include "tools/RandomETU.hpp"

#define PATH "../../client/assets/images/enemies/ennemy_9_102x34_34x34.png"
#define SIZE_X 34
#define SIZE_Y 34

class BWRobot : public Enemy {
private:
    const Engine::Size<double> _size = {SIZE_X, SIZE_Y};

public:
    explicit BWRobot(const Engine::Point<double> &pos = {0, 0});
};

#endif //RTYPE_BWROBOT_HPP
