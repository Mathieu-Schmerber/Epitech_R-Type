/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "TCP/TcpSocket.hpp"
#include "Client.hpp"

Session::Session(boost::asio::io_service &io_service, int id) : socket(io_service), _id(id)
{
    _data.resize(40);
}

tcp::socket &Session::get_socket()
{
    return this->socket;
}

void Session::start()
{
    socket.async_read_some(boost::asio::buffer(_data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred)
{
    std::cout << _data << std::endl;
    if (!err) {
        socket.async_read_some(boost::asio::buffer(_data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Client Disconnected id : " << s->getId() << std::endl;
    }
}

int Session::getId() const
{
    return this->_id;
}

/*===========================================================*/

Server::Server(short port) : _io_service(), _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)), _id(1),
    _lobbyManager()
{
    std::shared_ptr<Session> session = std::make_shared<Session>(_io_service, 0);
    _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
    _thread = std::thread([&] { this->_io_service.run(); } );
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err)
{
    if (!err) {
        std::cout << "New client connected" << std::endl;
        session->start();
        session = std::make_shared<Session>(_io_service, _id++);
        _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
        auto client = new (std::nothrow)Client(session);
        if (!client)
            return;
        _connected.push_back(client);
        std::cout << "ID new client : " << client->getId() << std::endl;
    } else {
        std::cerr << "err: " + err.message() << std::endl;
        session.reset();
    }
}

void Server::run()
{
    boost::asio::io_service io_serv;
    auto pouet = std::make_shared<Session>(io_serv, 1);
    Client cli(pouet);
    auto a = _lobbyManager.getLobbyById(1);
    if (a) {
        a->join(cli);
        a->run();
    }
    while (true) {
    }
}

void Server::stop()
{
    this->_io_service.stop();
}