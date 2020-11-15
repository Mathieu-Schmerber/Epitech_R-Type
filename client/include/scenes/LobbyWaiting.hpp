/*!
 * @file LobbyWaiting.hpp
 * @brief LobbyWaiting prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_LOBBYWAITING_HPP
#define RTYPE_LOBBYWAITING_HPP

#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

class LobbyWaiting : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

    public:
    /*!
     * \brief LobbyWaiting scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     * \param server server API to be stored as reference
     *
     * Create the "LobbyWaiting" scene
    */
    LobbyWaiting(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);

    std::shared_ptr<Engine::AWindow> getWindow() const;
    std::shared_ptr<NetworkAccess> getServer() const;
};

void goBackToCreateLobby(std::shared_ptr<Engine::AScene> &);
void goToInGamesScene(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_LOBBYWAITING_HPP
