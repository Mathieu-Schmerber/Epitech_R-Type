/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "TCP/TcpSocket.hpp"
#include "Client.hpp"

Server::Server(short port) : _io_service(), _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)), _id(1),
    _lobbyManager()
{
    std::shared_ptr<Client> session = std::make_shared<Client>(_io_service, 0, this);
    _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error, this));
    //_thread = std::thread([&] { this->_io_service.run(); } );
}

void Server::handle_accept(std::shared_ptr<Client> session, const boost::system::error_code &err, Server *server)
{
    if (!err) {
        std::cout << "New client connected" << std::endl;
        session->start();
        session = std::make_shared<Client>(_io_service, _id++, server);
        _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error, this));
        _connected.push_back(session);
    } else {
        std::cerr << "err: " + err.message() << std::endl;
        session.reset();
    }
}

void Server::run()
{
    this->_io_service.run();
}

void Server::stop()
{
    this->_io_service.stop();
}

LobbyManager &Server::getLobbyManager()
{
    return this->_lobbyManager;
}
