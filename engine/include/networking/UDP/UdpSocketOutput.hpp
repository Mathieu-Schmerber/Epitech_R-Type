/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_UDPSOCKETOUTPUT_HPP
#define RTYPE_UDPSOCKETOUTPUT_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace Engine {
    class UdpSocketOutput {
    public:
        explicit UdpSocketOutput(const std::string &ipToConnect, int portOut);
        void sendDataToServer(const std::vector<int> &in);
        ~UdpSocketOutput();
    private:
        void _stop();
        boost::asio::io_service _ioServiceOutput;
        udp::socket _socketOutput{_ioServiceOutput};
        udp::endpoint _remoteEndpointOutput{};
        std::thread _threadSender;
    };
}

#endif //RTYPE_UDPSOCKETOUTPUT_HPP
