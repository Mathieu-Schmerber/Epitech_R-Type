//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_CREATELOBBYCOMPONENT_HPP
#define RTYPE_CREATELOBBYCOMPONENT_HPP

#include "ecs/Component.hpp"

class CreateLobbyComponent : public Engine::Component {
    private:
    unsigned short _nbMaxClient;

    public:
    explicit CreateLobbyComponent() : _nbMaxClient(1), Engine::Component() {

    }
    void setNbMaxClient(unsigned short nbMaxOfClient) { _nbMaxClient = nbMaxOfClient; };
    [[nodiscard]] unsigned short getNbMaxClients() const { return _nbMaxClient;};
};

#endif //RTYPE_CREATELOBBYCOMPONENT_HPP
