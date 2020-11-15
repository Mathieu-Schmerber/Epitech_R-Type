/*!
 * @file PlayerAndStarshipSystem.hpp
 * @brief System to deal with lobbies
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP
#define RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class PlayerAndStarshipSystem : public Engine::System {
    private:
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;

    void updateFromServer();
    void handleLobbyJoin(std::shared_ptr<Engine::Entity> &);

    public:
    /*!
     * \brief PlayerAndStarship system constructor
     * \param server server API to be stored as reference
     * \param events events manager to be stored as reference
     * \param scene actual scene as reference
     *
     * Create the "PlayerAndStarship" system
    */
    PlayerAndStarshipSystem(std::shared_ptr<NetworkAccess> &server,
        std::shared_ptr<Engine::AEvents> &events,
        std::shared_ptr<Engine::AScene> &scene);

    /*!
     * \brief update function
     *
     * This function is called for each scene which has the PlayerAndStarship in its systems
    */
    void update() override;
};

#endif //RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP
