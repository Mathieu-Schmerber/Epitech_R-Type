//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SCENEMANAGER_HPP
#define RTYPE_SCENEMANAGER_HPP

#include <memory>
#include <map>
#include <ostream>
#include "AScene.hpp"
#include "networking/AServer.hpp"
#include "Graphical/AGraphical.hpp"

namespace Engine {

    class SceneManager {

    private:
        std::map<int, std::unique_ptr<Engine::AScene>> _scenes;
        int _current;

    public:
        explicit SceneManager() : _current(-1) {}
        ~SceneManager();

        void handleSwitchRequests();
        std::unique_ptr<Engine::AScene> &getCurrent();
        void switchScene(int id);
        void addScene(std::unique_ptr<Engine::AScene> scene);
    };

}


#endif //RTYPE_SCENEMANAGER_HPP
