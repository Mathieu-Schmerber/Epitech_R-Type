/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/AUdpSocketIO.hpp"

Engine::AUdpSocketIO::AUdpSocketIO(const std::string &ipServer, int portServer, int portClient) :
    UdpSocketInput(portClient), UdpSocketOutput(ipServer, portServer)
{
}
