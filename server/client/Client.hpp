/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CLIENT_HPP
#define RTYPE_CLIENT_HPP

#include "TCP/TcpSocket.hpp"
#include "networking/UDP/UdpSocketOutput.hpp"

class Client {
public:
    explicit Client(std::shared_ptr<Session> &session);
    [[nodiscard]] int getId() const;
    void sendToClient(std::vector<int> &toSend);
private:
    std::shared_ptr<Session> _session;
    std::shared_ptr<Engine::UdpSocketOutput> _socketOutput;
};

#endif //RTYPE_CLIENT_HPP
