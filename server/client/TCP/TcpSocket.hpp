/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_TCPSOCKET_HPP
#define RTYPE_TCPSOCKET_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include "LobbyManager.hpp"

using boost::asio::ip::tcp;

class Server;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service, int id, Server *server);

    tcp::socket& get_socket();
    void start();
    void handle_read(std::shared_ptr<Session>& s, const boost::system::error_code& err, size_t bytes_transferred);
    int getId() const;
private:
    tcp::socket socket;
    enum { max_length = 1024 };
    std::vector<int> _data;
    int _id;
    Server *_server;
};

class Client;

class Server {
public:
    explicit Server(short port);

    void handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& err, Server *server);
    [[noreturn]] void run();
    void stop();
private:
    boost::asio::io_service _io_service;
    tcp::acceptor _acceptor;
    std::vector<Client *> _connected{};
    int _id;
    std::thread _thread;
    LobbyManager _lobbyManager;
};

#endif //RTYPE_TCPSOCKET_HPP
