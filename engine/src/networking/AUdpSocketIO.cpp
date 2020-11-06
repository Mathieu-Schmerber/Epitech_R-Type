/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "networking/AUdpSocketIO.hpp"

Engine::AUdpSocketIO::AUdpSocketIO(const std::string &ipServer, int portServer, int portClient)
{
    _setupSend(ipServer, portServer);
    _setupReceive(portClient);
    _run();
}

Engine::AUdpSocketIO::~AUdpSocketIO()
{
    _stop();
}

void Engine::AUdpSocketIO::_setupSend(const std::string &ip, int port)
{
    _socketOutput = udp::socket(_ioServiceOutput);
    _socketOutput.open(udp::v4());
    _remoteEndpointOutput = udp::endpoint(address::from_string(ip), port);
    _socketOutput.connect(_remoteEndpointOutput);
}

void Engine::AUdpSocketIO::_setupReceive(int port)
{
    _socketInput = udp::socket(_ioServiceInput);
    _socketInput.open(udp::v4());
    _receiveBuffer.clear();
    _receiveBuffer.resize(240);
    _socketInput.bind(udp::endpoint(address::from_string("0.0.0.0"), port));
    _socketInput.async_receive_from(boost::asio::buffer(_receiveBuffer), _remoteEndpointInput,
        boost::bind(&AUdpSocketIO::_handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Engine::AUdpSocketIO::_handleReceive(const boost::system::error_code &error, size_t bytes)
{
    if (error) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        return;
    }
    std::cout << "RECEIVE : " << bytes << std::endl;
    _socketInput.async_receive_from(boost::asio::buffer(_receiveBuffer), _remoteEndpointInput,
        boost::bind(&AUdpSocketIO::_handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::vector<int> Engine::AUdpSocketIO::getDataFromServer() const
{
    return _receiveBuffer;
}

void Engine::AUdpSocketIO::sendDataToServer(const std::vector<int> &in)
{
    boost::system::error_code err;
    std::cout << "SEND : " << in.size() << std::endl;
    _socketOutput.send(boost::asio::buffer(in, in.size() * sizeof(int)), 0, err);
    if (err)
        std::cerr << err << std::endl;
}

void Engine::AUdpSocketIO::_run()
{
    _threadSender = std::thread([&] { _ioServiceOutput.run(); });
    _threadReceiver = std::thread([&] { _ioServiceInput.run(); });
}

void Engine::AUdpSocketIO::_stop()
{
    _ioServiceOutput.stop();
    _ioServiceInput.stop();
    _threadSender.join();
    _threadReceiver.join();
    _socketInput.close();
    _socketOutput.close();
}
