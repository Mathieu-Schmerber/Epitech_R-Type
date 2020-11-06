//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ASERVER_HPP
#define RTYPE_ASERVER_HPP

#include <string>
#include <memory>
#include "networking/ATcpSocket.hpp"
#include "networking/AUdpSocketIO.hpp"

namespace Engine {

    class AServer {

    protected:
        std::string _ip;
        int _port;
        std::unique_ptr<ATcpSocket> _tcpSocket;
        std::unique_ptr<AUdpSocketIO> _udpSocket;

    public:
        AServer(const std::string &ip, int port);
        ~AServer();

        [[nodiscard]] const std::unique_ptr<ATcpSocket> &getTcpSocket() const;
        [[nodiscard]] const std::unique_ptr<AUdpSocketIO> &getUdpSocket() const;
    };

}

#endif //RTYPE_ASERVER_HPP
