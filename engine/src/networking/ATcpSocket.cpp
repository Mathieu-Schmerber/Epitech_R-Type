/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/ATcpSocket.hpp"
#include <iostream>
#include <boost/bind.hpp>

Engine::ATcpSocket::ATcpSocket(const std::string &in, int port) : _endpoint(boost::asio::ip::address::from_string(in), port),
    _socket(_io_service)
{
    _socket.connect(_endpoint);
    _data.resize(40);
    _socket.async_read_some(boost::asio::buffer(_data, 40),
        boost::bind(&Engine::ATcpSocket::_handleRead, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    _thread = std::thread([&] { _io_service.run(); } );
}

void Engine::ATcpSocket::sendToServer(std::vector<int> &toSend)
{
    boost::asio::write(_socket, boost::asio::buffer(toSend));
}

std::vector<int> Engine::ATcpSocket::getDataFromServer()
{
    if (_queueData.empty()) {
        std::vector<int> output;
        output.push_back(0);
        return output;
    } else {
        std::vector<int> buffer = _queueData.front();

        _queueData.erase(_queueData.begin());
        return buffer;
    }
}

void Engine::ATcpSocket::_handleRead(const boost::system::error_code &error, std::size_t bytes)
{
    std::cout << "Hey, I receive something " << bytes << " : ";
    for (auto &a : _data)
        std::cout << a << " ";
    std::cout << std::endl;
    _queueData.push_back(_data);
    _socket.async_read_some(boost::asio::buffer(_data, 40),
        boost::bind(&Engine::ATcpSocket::_handleRead, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

Engine::ATcpSocket::~ATcpSocket()
{
    _io_service.stop();
    _thread.join();
    _socket.close();
}