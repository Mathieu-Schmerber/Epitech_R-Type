//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ATCPSOCKET_HPP
#define RTYPE_ATCPSOCKET_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Engine {
    class ATcpSocket {
    public:
        explicit ATcpSocket(const std::string &in, int port);
        void sendToServer(std::vector<int> &toSend);
        std::vector<int> getDataFromServer();
        ~ATcpSocket();
    private:
        void _handleRead(const boost::system::error_code &error, std::size_t bytes);
        boost::asio::io_service _io_service;
        tcp::endpoint _endpoint;
        tcp::socket _socket;
        std::vector<int> _data;
        std::vector<std::vector<int>> _queueData;
        std::thread _thread;
    };
}

#endif //RTYPE_ATCPSOCKET_HPP
