/*!
 * @file InGame.hpp
 * @brief InGame scene declaration
 * @authors Matthieu.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_INGAME_HPP
#define RTYPE_INGAME_HPP

#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "NetworkAccess.hpp"

class InGame : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::Entity> _quitButton;

    void initEntities() final;
    void initSystems() final;

public:
    /*!
     * \brief InGame scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     * \param server server API to be stored as reference
     *
     * Create the "InGame" scene
    */
    InGame(std::shared_ptr<Engine::AWindow> &window,
           std::shared_ptr<Engine::AEvents> &events,
           std::shared_ptr<NetworkAccess> &server);
    ~InGame() = default;

    void onFocus() override;
    void onExit() override;
    std::shared_ptr<Engine::Entity> getQuitButton() const;

};

void backToMainMenu(std::shared_ptr<Engine::AScene> &);


#endif //RTYPE_INGAME_HPP
