/*!
 * @file ClientNetworkSystem.hpp
 * @brief System to deal with client and network
 * @authors Matthieu.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_CLIENTNETWORKSYSTEM_HPP
#define RTYPE_CLIENTNETWORKSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"
#include "SocketParser.hpp"

#define UDP_ENTITY_SIZE 11
#define UDP_READ UDP_BUFFER_SIZE / UDP_ENTITY_SIZE

class ClientNetworkSystem : public Engine::System
{
private:
    std::vector<int> _lastData;
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;
    std::unique_ptr<SocketParser> _parser;

    void sendRawInputs();
    void receiveGameData();
    void readServerTCP();

public:
    /*!
     * \brief ClientNetWork system constructor
     * \param server server API to be stored as reference
     * \param events events manager to be stored as reference
     * \param scene actual scene as reference
     *
     * Create the "ClientNetwork" system
    */
    ClientNetworkSystem(std::shared_ptr<NetworkAccess> &server,
                        std::shared_ptr<Engine::AEvents> &events,
                        std::shared_ptr<Engine::AScene> &scene);

    /*!
     * \brief update function
     *
     * This function is called for each scene which has the LobbyNetworkSystem in its systems
    */
    void update() override;
};


#endif //RTYPE_CLIENTNETWORKSYSTEM_HPP
