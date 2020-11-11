/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "Enemy.hpp"

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <stdio.h>
#endif

extern "C" IEnemy *newInstance()
{
    return new Enemy("hihi");
}

Enemy::Enemy(std::string test) : _test(test)
{

}