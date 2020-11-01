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
    std::shared_ptr<Engine::AGraphical> _graph;
    Engine::AServer *_server;

    void run();

public:
    Core();
    void start();
};

#endif //RTYPE_CORE_HPP
