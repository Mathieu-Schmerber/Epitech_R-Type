/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Core.hpp"

Core::Core() : server(4242, this)
{

}

void Core::run()
{
    server.start();
    while (true);
    server.stop();
}