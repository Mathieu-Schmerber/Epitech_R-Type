/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "FloatingRobot.hpp"

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <stdio.h>
#endif

extern "C" {
    #if defined(_WIN32) || defined(WIN32)
    __declspec(dllexport) 
    #endif
    Enemy* newInstance()
    {
        return new FloatingRobot();
    }
}