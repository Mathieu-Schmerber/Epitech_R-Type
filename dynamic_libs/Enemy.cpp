/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "Enemy.hpp"

#include <utility>

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <stdio.h>
#endif

extern "C" {
    #if defined(_WIN32) || defined(WIN32)
    __declspec(dllexport) 
    #endif
    IEnemy* newInstance()
    {
        return new Enemy();
    }
}

Enemy::Enemy(std::string test) : _test(std::move(test))
{
    std::cout << _test << std::endl;
}