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
    _connected.push_back(session);
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
        for (auto a : this->_lobbyManager.getAvailableLobbies()) {
            std::vector<int> toSend;
            toSend.clear();
            toSend.push_back(7); //Message len
            toSend.push_back(1); //Id for create Lobby
            toSend.push_back(a->getId());
            toSend.push_back(a->getPort());
            toSend.push_back(a->getSlots());
            toSend.push_back(0); //Master client Id
            toSend.push_back(a->getNbPlayers());
            std::cout << "Size : " << _connected.size() << std::endl;
            for (const auto & pouet : _connected) {
                std::cout << pouet->getId() << std::endl;
            }
            std::shared_ptr<Client> newSession = _connected.at(((_connected.size() - 2) < 0 ? 0 : _connected.size() - 2));
            std::cout << "Send to session " << newSession->getId() << " " << ((_connected.size() - 2) < 0 ? 0 : _connected.size() - 2) << std::endl;
            newSession->sendToClientTcp(toSend);
        }
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

std::vector<std::shared_ptr<Client>> Server::getClientList() const
{
    return this->_connected;
}

void Server::removeClient(std::shared_ptr<Client> &cli)
{
    for (auto a = _connected.begin() ; a != _connected.end(); a++)
        if (a->get()->getId() == cli->getId())
            _connected.erase(a);
}
