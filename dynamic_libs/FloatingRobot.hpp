/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_FLOATINGROBOT_HPP
#define RTYPE_FLOATINGROBOT_HPP

#include "entities/Enemy.hpp"

#define PATH "../../client/assets/images/enemies/ennemy_5_99x33_33x33.png"
#define SIZE_X 33
#define SIZE_Y 33

class FloatingRobot : public Enemy {
private:
    const Engine::Size<double> _size = {SIZE_X, SIZE_Y};

public:
    explicit FloatingRobot(const Engine::Point<double> &pos = {0, 0});
};

#endif //RTYPE_FLOATINGROBOT_HPP
