/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_TCPSOCKET_HPP
#define RTYPE_TCPSOCKET_HPP

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service);

    tcp::socket& get_socket();
    void start();
    void handle_read(std::shared_ptr<Session>& s, const boost::system::error_code& err, size_t bytes_transferred);
private:
    tcp::socket socket;
    enum { max_length = 1024 };
    char data[max_length]{};
};

class Server {
public:
    Server(short port);

    void handle_accept(std::shared_ptr<Session> session,
        const boost::system::error_code& err);
    void start();
    void stop();
private:
    boost::asio::io_service io_service;
    tcp::acceptor acceptor;
    std::thread *thread = nullptr;
};

#endif //RTYPE_TCPSOCKET_HPP
