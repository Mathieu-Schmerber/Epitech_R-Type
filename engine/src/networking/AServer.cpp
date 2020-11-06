//
// Created by mathi on 29/10/2020.
//

#include "networking/AServer.hpp"

Engine::AServer::AServer(const std::string &ip, short serverPort, short clientPort) : _ip(ip), _port(serverPort), _clientPort(clientPort) {}

const std::unique_ptr<Engine::ATcpSocket> &Engine::AServer::getTcpSocket() const {
    return _tcpSocket;
}

const std::unique_ptr<Engine::AUdpSocketIO> &Engine::AServer::getUdpSocket() const {
    return _udpSocket;
}

void Engine::AServer::openSockets()
{
    try {
        this->_tcpSocket = std::make_unique<Engine::ATcpSocket>(_ip, _port);
        this->_udpSocket = std::make_unique<Engine::AUdpSocketIO>(_ip, _port, _clientPort);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}