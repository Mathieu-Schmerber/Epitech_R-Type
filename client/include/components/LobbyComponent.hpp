//
// Created by paul on 11/6/20.
//

#ifndef RTYPE_LOBBYCOMPONENT_HPP
#define RTYPE_LOBBYCOMPONENT_HPP

#include "ecs/Component.hpp"
#include <memory>

namespace Engine {
    class LobbyComponent : public Engine::Component {
        private:
            short _port;
            std::string _ip;
            std::string _name;
            unsigned short _nbMaxClient;
            unsigned int _idClientMaster;

        public:
            LobbyComponent(short port, const std::string &ip, const std::string &name, unsigned short nbMaxClient, unsigned int idClientMaster)
                : _port(port), _ip(ip), _name(name), _nbMaxClient(nbMaxClient), _idClientMaster(idClientMaster) {}
    };
}

#endif //RTYPE_LOBBYCOMPONENT_HPP
