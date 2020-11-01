//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <memory>
#include <iostream>

#include "Graphical/AGraphical.hpp"
#include "SceneManager.hpp"

class Core
{
private:
    std::unique_ptr<Engine::AGraphical> _graph;
    std::unique_ptr<Engine::AServer> _server;
    std::unique_ptr<Engine::SceneManager> _sceneManager;

    void run();
    void initScenes();

public:
    Core();
    void start();
};

#endif //RTYPE_CORE_HPP
