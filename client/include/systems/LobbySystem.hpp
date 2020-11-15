/*!
 * @file LobbySystem.hpp
 * @brief System to deal with lobbies
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_LOBBYSYSTEM_HPP
#define RTYPE_LOBBYSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class LobbySystem : public Engine::System {
    private:
        std::shared_ptr<NetworkAccess> _server;
        std::shared_ptr<Engine::AEvents> _events;
        std::shared_ptr<Engine::AScene> _scene;

        void updateFromServer();
        void handleScroll();
        void handleLobbyJoin(std::shared_ptr<Engine::Entity> &lobby);

    public:
        /*!
         * \brief Lobby system constructor
         * \param server server API to be stored as reference
         * \param events events manager to be stored as reference
         * \param scene actual scene as reference
         *
         * Create the "Lobby" system
        */
        LobbySystem(std::shared_ptr<NetworkAccess> &server,
                    std::shared_ptr<Engine::AEvents> &events,
                    std::shared_ptr<Engine::AScene> &scene);
        /*!
         * \brief scrollDownLobbies method
         *
         * This method is called when the user want to scroll down the lobbies in the LobbyList scene
        */
        void scrollDownLobbies();
        /*!
         * \brief scrollUpLobbies method
         *
         * This method is called when the user want to scroll up the lobbies in the LobbyList scene
        */
        void scrollUpLobbies();
        /*!
         * \brief update function
         *
         * This function is called for each scene which has the LobbySystem in its systems
        */
        void update() override;
};


#endif //RTYPE_LOBBYSYSTEM_HPP
