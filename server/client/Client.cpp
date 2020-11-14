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
        s->get_socket().close();
        this->_server->removeClient(s);
        return;
    }



    std::cout << "Receive from IP [" << socket.remote_endpoint().address().to_string() << "] : ";
    for (auto ia : _data) {
        std::cout << ia << " ";
    }
    std::cout << std::endl;


    if (_data.at(0) < 2)
        return;
    if (_data.at(1) == 0) {
        //Join a lobby
        for (auto a : this->_server->getLobbyManager().getAvailableLobbies()) {
            if (a->getId() == _data.at(2))
                a->join(std::shared_ptr<Client>(this));
        }
    } else if (_data.at(1) == 1) {
        //Create a Lobby
        auto newLobby = this->_server->getLobbyManager().addLobby(_data.at(2));
        if (!newLobby)
            return;
        newLobby->join(s);
        _currentLobby = newLobby;
        std::vector<int> answerToClient;
        answerToClient.push_back(3);
        answerToClient.push_back(42);
        answerToClient.push_back(newLobby->getPort());
        s->sendToClientTcp(answerToClient);
        std::vector<int> toAll;
        toAll.push_back(7);
        toAll.push_back(1);
        toAll.push_back(newLobby->getId());
        toAll.push_back(newLobby->getPort());
        toAll.push_back((int)newLobby->getSlots());
        toAll.push_back(_id);
        toAll.push_back((int)newLobby->getNbPlayers());
        for (auto &a : this->_server->getClientList()) {
            try {
                a->sendToClientTcp(toAll);
            } catch (std::exception &e) {
                std::cerr << "Send to clients errors : " << e.what() << std::endl;
            }
        }
    } else if (_data.at(1) == 43) {
        if (_data.at(0) != 3)
            return;
        _socketOutput = std::make_shared<Engine::UdpSocketOutput>(this->get_socket().remote_endpoint().address().to_string(), _data.at(2));
    } else if (_data.at(1) == 44) {
        if (_data.at(0) != 2)
            return;
        if (_currentLobby)
            _currentLobby->run();
    }
}

int Client::getId() const
{
    return this->_id;
}

void Client::sendToClient(const std::vector<int> &in)
{
    this->_socketOutput->sendDataToServer(in);
}

void Client::sendToClientTcp(const std::vector<int> &in)
{
    if (this->get_socket().is_open())
        this->get_socket().write_some(boost::asio::buffer(in));
}
