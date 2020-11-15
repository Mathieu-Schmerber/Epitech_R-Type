/*!
 * @file LobbyList.hpp
 * @brief LobbyList prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_LOBBYLIST_HPP
#define RTYPE_LOBBYLIST_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/LobbyCard.hpp"
#include "systems/LobbySystem.hpp"

class LobbyList : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

    public:
    /*!
     * \brief LobbyList scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     * \param server server API to be stored as reference
     *
     * Create the "LobbyList" scene
    */
    LobbyList(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);
    /*!
     * \brief getLobbySystem getter
     *
     * Return the LobbySystem of the LobbyList scene
    */
    const std::unique_ptr<Engine::System> &getLobbySystem() const;

    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void scrollDownLobby(std::shared_ptr<Engine::AScene> &);
void scrollUpLobby(std::shared_ptr<Engine::AScene> &);
void goToCreateLobbyScene(std::shared_ptr<Engine::AScene> &);
void goToMenuScene(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_LOBBYLIST_HPP