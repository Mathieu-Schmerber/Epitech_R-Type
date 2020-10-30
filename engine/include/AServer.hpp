//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ASERVER_HPP
#define RTYPE_ASERVER_HPP

#include <string>
#include <memory>
#include "ATcpSocket.hpp"
#include "AUdpSocket.hpp"

namespace Engine {

    class AServer {

    protected:
        std::string _ip;
        int _port;
        std::unique_ptr<ATcpSocket> _tcpSocket;
        std::unique_ptr<AUdpSocket> _udpSocket;

    public:
        AServer(const std::string &ip, int port);
        ~AServer();

    };

}

#endif //RTYPE_ASERVER_HPP
