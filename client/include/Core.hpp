//
// Created by mathi on 29/10/2020.
//

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
    Core();
    ~Core() = default;
    void start();
};

#endif //RTYPE_CORE_HPP
