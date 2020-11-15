/*!
 * @file CreateLobby.hpp
 * @brief CreateLobby prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_CREATELOBBY_HPP
#define RTYPE_CREATELOBBY_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

class CreateLobby : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::Entity> _textNbPlayerMax;

    void initEntities() final;
    void initSystems() final;

    public:
    /*!
     * \brief CreateLobby scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     * \param server server API to be stored as reference
     *
     * Create the "CreateLobby" scene
    */
    CreateLobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);

    std::shared_ptr<Engine::Entity> getTextNbPlayerMax() const;
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void increaseNbOfClientsCb(std::shared_ptr<Engine::AScene> &);
void decreaseNbOfClientsCb(std::shared_ptr<Engine::AScene> &);
void goToLobbyWaiting(std::shared_ptr<Engine::AScene> &);
void goBackToLobbyList(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_CREATELOBBY_HPP
