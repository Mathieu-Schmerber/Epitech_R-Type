/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CLIENT_HPP
#define RTYPE_CLIENT_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "networking/UDP/UdpSocketOutput.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class Server;

class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_service& io_service, int id, Server *server);

    tcp::socket& get_socket();
    void start();
    void handle_read(std::shared_ptr<Client>& s, const boost::system::error_code& err, size_t bytes_transferred);
    void sendToClient(const std::vector<int> &in);
    int getId() const;
private:
    tcp::socket socket;
    enum { max_length = 1024 };
    std::vector<int> _data;
    int _id;
    Server *_server;
};

#endif //RTYPE_CLIENT_HPP