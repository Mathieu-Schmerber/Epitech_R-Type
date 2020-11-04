//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ASCENE_HPP
#define RTYPE_ASCENE_HPP

#include <ostream>
#include "ecs/System.hpp"
#include "sceneManagement/AEntityGroup.hpp"
#include "sceneManagement/SceneRequest.hpp"

namespace Engine {

    class AScene : public std::enable_shared_from_this<AScene> {

    protected:
        int _sceneId;
        std::vector<Engine::SceneRequest> _requests;
        std::vector<std::unique_ptr<Engine::System>> _systems;
        std::vector<std::shared_ptr<Engine::Entity>> _entities;
        std::vector<std::shared_ptr<Engine::AEntityGroup>> _groups;

        virtual void initEntities();
        virtual void initSystems();

    public:
        explicit AScene(int id);
        ~AScene();

        virtual void onFocus() {}
        virtual void onExit() {}

        void updateDeltatime(double delta);
        [[nodiscard]] int getId() const;
        void spawnEntity(std::shared_ptr<Entity> entity);
        [[nodiscard]] std::vector<Engine::SceneRequest> getRequests() const;
        void pushRequest(const SceneRequest &request);
        void clearRequests();
        void addGroupAccess(const std::shared_ptr<Engine::AEntityGroup> &group);
        [[nodiscard]] std::vector<std::shared_ptr<Engine::AEntityGroup>> getGroupAccess() const;
        void onGroupUpdate(const std::shared_ptr<AEntityGroup> &group);
        virtual void update();
    };

}

#endif //RTYPE_ASCENE_HPP
