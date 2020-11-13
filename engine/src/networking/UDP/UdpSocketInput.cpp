/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/UDP/UdpSocketInput.hpp"

UdpSocketInput::UdpSocketInput(int portIn)
{
    _socketInput = udp::socket(_ioServiceInput);
    _socketInput.open(udp::v4());
    _receiveBuffer.clear();
    _receiveBuffer.resize(UDP_BUFFER_SIZE, -1);
    _socketInput.bind(udp::endpoint(address::from_string("0.0.0.0"), portIn));
    _socketInput.async_receive_from(boost::asio::buffer(_receiveBuffer), _remoteEndpointInput,
        boost::bind(&UdpSocketInput::_handleReceive, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    _threadReceiver = std::thread([&] { _ioServiceInput.run(); } );
}

std::vector<int> UdpSocketInput::getDataFromServer() const
{
    return _receiveBuffer;
}

void UdpSocketInput::_handleReceive(const boost::system::error_code &error, size_t bytes)
{
    if (error) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        return;
    }
    _socketInput.async_receive_from(boost::asio::buffer(_receiveBuffer), _remoteEndpointInput,
        boost::bind(&UdpSocketInput::_handleReceive, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

UdpSocketInput::~UdpSocketInput()
{
    _ioServiceInput.stop();
    _threadReceiver.join();
}