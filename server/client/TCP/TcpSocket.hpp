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
#include "Client.hpp"

using boost::asio::ip::tcp;

class Server {
public:
    explicit Server(short port);

    void handle_accept(std::shared_ptr<Client> session, const boost::system::error_code& err, Server *server);
    [[noreturn]] void run();
    LobbyManager &getLobbyManager();
    [[nodiscard]] std::vector<std::shared_ptr<Client>> getClientList() const;
    void removeClient(std::shared_ptr<Client> &cli);
    void stop();
private:
    boost::asio::io_service _io_service;
    tcp::acceptor _acceptor;
    std::vector<std::shared_ptr<Client>> _connected{};
    int _id;
    LobbyManager _lobbyManager;
};

#endif //RTYPE_TCPSOCKET_HPP
