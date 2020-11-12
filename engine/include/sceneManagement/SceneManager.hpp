//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SCENEMANAGER_HPP
#define RTYPE_SCENEMANAGER_HPP

#include <memory>
#include <map>
#include <ostream>
#include "sceneManagement/AScene.hpp"
#include "sceneManagement/AEntityGroup.hpp"
#include "networking/AServer.hpp"
#include "graphical/AGraphical.hpp"

namespace Engine {

    class SceneManager {

    private:
        std::map<int, std::unique_ptr<Engine::AScene>> _scenes;
        std::map<int, std::shared_ptr<Engine::AEntityGroup>> _groups;
        int _current;

        void parseRequest(const Engine::SceneRequest &request);
    public:
        explicit SceneManager() : _current(-1) {}
        ~SceneManager();

        void handleSceneRequests();
        void handleTime(float deltatime);

        // Group
        std::shared_ptr<Engine::AEntityGroup> addGroup(int id, const std::vector<std::shared_ptr<Engine::Entity>> &entities = {});
        std::shared_ptr<Engine::AEntityGroup> addGroup(int id, std::shared_ptr<Engine::AEntityGroup> group);
        void addToGroup(int id, std::shared_ptr<Engine::Entity> entity);
        void addToGroup(int id, std::vector<std::shared_ptr<Engine::Entity>> &entities);
        void setAccessGroup(int scene, int group);
        void setAccessGroup(int scene, const std::vector<int> &groups);

        // Scenes
        [[nodiscard]] std::unique_ptr<Engine::AScene> &getCurrent();
        void switchScene(int id);
        void addScene(std::unique_ptr<Engine::AScene> scene);
    };

}


#endif //RTYPE_SCENEMANAGER_HPP
