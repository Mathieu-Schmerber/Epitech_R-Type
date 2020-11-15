/*!
 * @file Core.hpp
 * @brief Core client declaration
 * @authors Matthieu.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <memory>
#include <iostream>
#include "graphical/AGraphical.hpp"
#include "sceneManagement/SceneManager.hpp"
#include "tools/Timer.hpp"
#include "NetworkAccess.hpp"

class Core
{
private:
    std::unique_ptr<Engine::AGraphical> _graph;
    std::shared_ptr<NetworkAccess> _server;
    std::unique_ptr<Engine::SceneManager> _sceneManager;
    std::unique_ptr<Engine::Timer> _timer;

    void run();
    void setupGroups();
    void initScenes();

public:
    /*!
    * \brief Core constructor
    *
    * Create the Core by setting all his member variables with determined value
   */
    explicit Core(const std::string &ip);
	
    /*!
    * \brief Core default destructor
    *
    * Destruct the core once game is finished
   */

    ~Core() = default;
	
    /*!
    * \brief Start the game (client side)
    *
   */
    void start();
};

#endif //RTYPE_CORE_HPP
