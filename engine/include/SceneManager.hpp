//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SCENEMANAGER_HPP
#define RTYPE_SCENEMANAGER_HPP

#include <memory>
#include <map>
#include "AScene.hpp"
#include "AServer.hpp"
#include "Graphical/AWindow.hpp"

namespace Engine {

    class SceneManager {

    private:
        std::map<int, Engine::AScene *> _scenes;
        int _current;
        Engine::AWindow *_window;
        Engine::AServer *_server;
        static Engine::SceneManager _instance;

        SceneManager();

    public:
        static Engine::SceneManager &get();
        static Engine::AScene *getCurrent();
        static void switchScene(int id);
        static Engine::AScene *createScene(Engine::AScene *scene);
        static void setWindow(Engine::AWindow *window);
        static void setServer(Engine::AServer *server);
        static Engine::AWindow *getWindow();
        static Engine::AServer *getServer();

    };

}


#endif //RTYPE_SCENEMANAGER_HPP
