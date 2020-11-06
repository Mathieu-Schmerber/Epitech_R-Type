//
// Created by mathi on 29/10/2020.
//

#include "networking/AServer.hpp"

Engine::AServer::AServer(const std::string &ip, int port) : _ip(ip), _port(port){}

Engine::AServer::~AServer()
{

}

const std::unique_ptr<Engine::ATcpSocket> &Engine::AServer::getTcpSocket() const {
    return _tcpSocket;
}

const std::unique_ptr<Engine::AUdpSocketIO> &Engine::AServer::getUdpSocket() const {
    return _udpSocket;
}
