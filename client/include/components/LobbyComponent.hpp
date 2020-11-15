/*!
 * @file LobbyComponent.hpp
 * @brief LobbyComponent prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_LOBBYCOMPONENT_HPP
#define RTYPE_LOBBYCOMPONENT_HPP

#include <memory>
#include "ecs/Component.hpp"

class LobbyComponent : public Engine::Component {
    private:
        short _port;
        unsigned short _lobbyId;
        unsigned short _nbMaxClient;
        unsigned short _nbActualClient;
        unsigned int _idClientMaster;


    public:
        /*!
         * \brief LobbyComponent constructor
         *
         * Basic lobbyComponent with all info set to 0 by default.
        */
        explicit LobbyComponent() : _port(0), _lobbyId(0), _nbActualClient(0), _nbMaxClient(0), _idClientMaster(0), Engine::Component() {}
        /*!
         * \brief LobbyComponent constructor
         * \param port lobby's port
         * \param lobbyId lobby's id
         * \param nbMaxClient lobby's number max of clients
         * \param nbActualClient lobby's actual number of clients (can be updated)
         * \param idClientMaster lobby client master id
         *
         * Contain necessary lobby's information
        */
        LobbyComponent(short port, unsigned int lobbyId, unsigned short nbMaxClient, unsigned int nbActualClient,
                       unsigned int idClientMaster)
                : _port(port), _lobbyId(lobbyId), _nbActualClient(nbActualClient), _nbMaxClient(nbMaxClient),
                  _idClientMaster(idClientMaster), Engine::Component() {}

        [[nodiscard]] short getPort() const { return _port; };

        [[nodiscard]] unsigned short getLobbyId() const { return _lobbyId; };

        [[nodiscard]] unsigned short getNbMaxClient() const { return _nbMaxClient; };

        [[nodiscard]] unsigned short getNbActualClient() const { return _nbActualClient; };

        void setNbActualClient(unsigned short nbOfClient) { _nbActualClient = nbOfClient; };

        [[nodiscard]] unsigned int getClientMasterId() const { return _idClientMaster; };
};

#endif //RTYPE_LOBBYCOMPONENT_HPP
