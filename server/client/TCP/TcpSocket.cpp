/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "TcpSocket.hpp"
#include "CoreServer.hpp"
#include "Client.hpp"

Session::Session(boost::asio::io_service &io_service, CoreServer *core) : socket(io_service), _core(core)
{
    if (_core)
        _id = _core->getNewId();
    else
        _id = 0;
}

tcp::socket &Session::get_socket()
{
    return this->socket;
}

void Session::start()
{
    socket.async_read_some(boost::asio::buffer(data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred)
{
    std::cout << data << std::endl;
    if (!err) {
        socket.async_read_some(boost::asio::buffer(data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Client Disconnected id " << s->getId() << std::endl;
        if (_core)
            _core->removeClient(s->getId());
    }
}

int Session::getId() const
{
    return this->_id;
}

/*===========================================================*/

Server::Server(short port, CoreServer *core) : _io_service(), _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)), _core(core)
{}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err)
{
    if (!err) {
        std::cout << "New client connected" << std::endl;
        session->start();
        session = std::make_shared<Session>(_io_service, _core);
        _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
        auto client = std::make_shared<Client>(session);
        std::cout << "ID new client : " << client->getId() << std::endl;
        if (this->_core)
            this->_core->setNewClient(client);
    } else {
        std::cerr << "err: " + err.message() << std::endl;
        session.reset();
    }
}

void Server::start()
{
    std::shared_ptr<Session> session = std::make_shared<Session>(_io_service, _core);
    std::cout << "First id " << session->getId() << std::endl;
    _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
    _thread = new (std::nothrow) std::thread([&] { this->_io_service.run(); });
}

void Server::stop()
{
    this->_io_service.stop();
    this->_thread->join();
}