/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_UDPSOCKETINPUT_HPP
#define RTYPE_UDPSOCKETINPUT_HPP

#ifdef _WIN32
#define _WIN32_WINNT 0x0601
#endif

#define UDP_BUFFER_SIZE 1000

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class UdpSocketInput {
public:
    explicit UdpSocketInput(int portIn);
    [[nodiscard]] std::vector<int> getDataFromServer() const;
    ~UdpSocketInput();
private:
    void _handleReceive(const boost::system::error_code &error, size_t bytes);
    boost::asio::io_service _ioServiceInput;
    udp::socket _socketInput{_ioServiceInput};
    udp::endpoint _remoteEndpointInput{};
    std::vector<int> _receiveBuffer;
    std::thread _threadReceiver;
};

#endif //RTYPE_UDPSOCKETINPUT_HPP
