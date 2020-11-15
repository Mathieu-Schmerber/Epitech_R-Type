//
// Created by mathi on 29/10/2020.
//

#include "networking/AServer.hpp"
#include "tools/EngineExceptions.hpp"

Engine::AServer::AServer(const std::string &ip, short serverPort, short clientPort) : _ip(ip), _port(serverPort), _clientPort(clientPort)
{
    try {
        std::cout << "Try to connect to : " << _ip << ":" << _port << std::endl;
        this->_tcpSocket = std::make_unique<Engine::ATcpSocket>(_ip, _port);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw Engine::ConnectError("Unable to connect to " + _ip + ":" + std::to_string(_port));
    }
}

const std::unique_ptr<Engine::ATcpSocket> &Engine::AServer::getTcpSocket() const {
    return _tcpSocket;
}

const std::unique_ptr<Engine::AUdpSocketIO> &Engine::AServer::getUdpSocket() const {
    return _udpSocket;
}

int Engine::AServer::getPortServer() const
{
    return _clientPort;
}

void Engine::AServer::openSockets(int portServer)
{
    try {
        bool error = true;

        for (int a = 0; a < 100 && error; ++a) {
            try {
                this->_udpSocket = std::make_unique<Engine::AUdpSocketIO>(_ip, portServer, _clientPort);
                error = false;
            } catch (std::exception &e) {
                std::cerr << e.what() << ": trying another port" << std::endl;
                _clientPort++;
                error = true;
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}