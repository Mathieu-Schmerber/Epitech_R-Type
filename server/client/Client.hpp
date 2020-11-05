/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CLIENT_HPP
#define RTYPE_CLIENT_HPP

#include "TcpSocket.hpp"

class Client {
public:
    explicit Client(std::shared_ptr<Session> &session);
    [[nodiscard]] int getId() const;
private:
    std::shared_ptr<Session> _session;
};

#endif //RTYPE_CLIENT_HPP
