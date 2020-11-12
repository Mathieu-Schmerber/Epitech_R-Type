/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Client.hpp"
#include "TcpSocket.hpp"

Client::Client(boost::asio::io_service &io_service, int id, Server *server) : socket(io_service), _id(id), _server(server)
{
    _socketOutput = std::make_shared<Engine::UdpSocketOutput>("127.0.0.1", 4242);
    _data.resize(40);
}

tcp::socket &Client::get_socket()
{
    return this->socket;
}

void Client::start()
{
    socket.async_read_some(boost::asio::buffer(_data, max_length), boost::bind(&Client::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Client::handle_read(std::shared_ptr<Client> &s, const boost::system::error_code &err, size_t bytes_transferred)
{
    if (!err) {
        socket.async_read_some(boost::asio::buffer(_data, max_length), boost::bind(&Client::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Client Disconnected id : " << s->getId() << std::endl;
        return;
    }
    if (_data.at(0) < 2)
        return;
    if (_data.at(1) == 1) {
        //Join a lobby
        for (auto a : this->_server->getLobbyManager().getAvailableLobbies()) {
            if (a->getId() == _data.at(2))
                a->join(std::shared_ptr<Client>(this));
        }
    }
}

int Client::getId() const
{
    return this->_id;
}

void Client::sendToClient(const std::vector<int> &in)
{

}
