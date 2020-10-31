//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <memory>
#include "SceneManager.hpp"

class Core
{
private:
    Engine::AWindow *_window;
    Engine::AServer *_server;

public:
    Core();
    void start();
};

#endif //RTYPE_CORE_HPP
