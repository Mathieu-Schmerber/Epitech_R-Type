/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include <memory>
#include "Client.hpp"

Client::Client(std::shared_ptr<Session> &session) : _session(session)
{
    _socketOutput = std::make_shared<Engine::UdpSocketOutput>("127.0.0.1", 4242);
}

int Client::getId() const
{
    return _session->getId();
}

void Client::sendToClient(std::vector<int> &toSend)
{
    _socketOutput->sendDataToServer(toSend);
}
