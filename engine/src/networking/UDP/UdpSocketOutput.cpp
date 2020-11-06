/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include <networking/UDP/UdpSocketOutput.hpp>

Engine::UdpSocketOutput::UdpSocketOutput(const std::string &ip, int port)
{
    _socketOutput = udp::socket(_ioServiceOutput);
    _socketOutput.open(udp::v4());
    _remoteEndpointOutput = udp::endpoint(address::from_string(ip), port);
    _socketOutput.connect(_remoteEndpointOutput);
    _threadSender = std::thread([&] {_ioServiceOutput.run(); });
}

void Engine::UdpSocketOutput::sendDataToServer(const std::vector<int> &in)
{
    boost::system::error_code err;
    std::cout << "SEND : " << in.size() << std::endl;
    _socketOutput.send(boost::asio::buffer(in, in.size() * sizeof(int)), 0, err);
    if (err)
        std::cerr << err << std::endl;
}

Engine::UdpSocketOutput::~UdpSocketOutput()
{
    _stop();
}

void Engine::UdpSocketOutput::_stop()
{
    _ioServiceOutput.stop();
    _threadSender.join();
    _socketOutput.close();
}