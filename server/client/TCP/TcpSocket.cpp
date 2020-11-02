/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "TcpSocket.hpp"

Session::Session(boost::asio::io_service &io_service, Core *core) : socket(io_service), _core(core) {}

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
    std::cout << s << std::endl;
    if (!err)
        socket.async_read_some(boost::asio::buffer(data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    else
        std::cerr << "err (recv): " << err.message() << std::endl;
}

/*===========================================================*/

Server::Server(short port, Core *core) : _io_service(), _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)), _core(core)
{
    std::shared_ptr<Session> session = std::make_shared<Session>(_io_service, _core);
    _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err)
{
    if (!err) {
        std::cout << "New client connected" << std::endl;
        session->start();
        session = std::make_shared<Session>(_io_service, _core);
        _acceptor.async_accept(session->get_socket(), boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
    } else {
        std::cerr << "err: " + err.message() << std::endl;
        session.reset();
    }
}

void Server::start()
{
    _thread = new (std::nothrow) std::thread([&] { this->_io_service.run(); });
}

void Server::stop()
{
    this->_io_service.stop();
    this->_thread->join();
}