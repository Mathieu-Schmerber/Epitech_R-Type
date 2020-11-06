//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_AUDPSOCKETIO_HPP
#define RTYPE_AUDPSOCKETIO_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace Engine {
    class AUdpSocketIO {
    public:
        explicit AUdpSocketIO(const std::string &ipServer, int portServer, int portClient);
        ~AUdpSocketIO();
        [[nodiscard]] std::vector<int> getDataFromServer() const;
        void sendDataToServer(const std::vector<int> &in);
    private:
        void _setupSend(const std::string &ip, int port);
        void _setupReceive(int port);
        void _run();
        void _stop();

        void _handleReceive(const boost::system::error_code &error, size_t bytes);
        boost::asio::io_service _ioServiceOutput;
        boost::asio::io_service _ioServiceInput;
        udp::socket _socketInput{_ioServiceInput};
        udp::socket _socketOutput{_ioServiceOutput};
        udp::endpoint _remoteEndpointOutput{};
        udp::endpoint _remoteEndpointInput{};
        std::vector<int> _receiveBuffer;
        std::thread _threadSender;
        std::thread _threadReceiver;
    };
}

#endif //RTYPE_AUDPSOCKETIO_HPP
