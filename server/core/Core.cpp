/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Core.hpp"
#include "TcpSocket.hpp"

Core::Core()
{

}

void Core::run()
{
    Server server(4242);

    server.start();
    Sleep(5000);
    server.stop();
}