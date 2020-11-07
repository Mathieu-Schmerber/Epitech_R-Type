/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/ATcpSocket.hpp"
#include <iostream>

Engine::ATcpSocket::ATcpSocket(const std::string &in, int port) : _endpoint(boost::asio::ip::address::from_string(in), port),
    _socket(_io_service)
{
    _socket.connect(_endpoint);
}

void Engine::ATcpSocket::sendToServer(std::vector<int> &toSend)
{
    boost::asio::write(_socket, boost::asio::buffer(toSend));
}

std::vector<int> Engine::ATcpSocket::getDataFromServer()
{
    std::vector<int> buffer;
    size_t len = _socket.read_some(boost::asio::buffer(buffer));

    std::cout << "=====================" << std::endl;
    std::cout << "Size read : " << len << std::endl;
    for (auto &a : buffer) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    return buffer;
}