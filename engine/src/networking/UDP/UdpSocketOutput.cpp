/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/UDP/UdpSocketOutput.hpp"

Engine::UdpSocketOutput::UdpSocketOutput(const std::string &ipToConnect, int portOut)
{
    _socketOutput = udp::socket(_ioServiceOutput);
    _socketOutput.open(udp::v4());
    _remoteEndpointOutput = udp::endpoint(address::from_string(ipToConnect), portOut);
    _socketOutput.connect(_remoteEndpointOutput);
}

void Engine::UdpSocketOutput::sendDataToServer(const std::vector<int> &in)
{
    boost::system::error_code err;
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
    _socketOutput.close();
}