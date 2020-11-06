//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ATCPSOCKET_HPP
#define RTYPE_ATCPSOCKET_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <boost/asio.hpp>

namespace Engine {
    class ATcpSocket {
    public:
        ATcpSocket(const std::string &in, int port);
    private:

    };
}

#endif //RTYPE_ATCPSOCKET_HPP
