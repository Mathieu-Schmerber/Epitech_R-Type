/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "Enemy.hpp"

extern "C" IEnemy *newInstance()
{
    return new Enemy("hihi");
}

Enemy::Enemy(std::string test) : _test(test)
{

}