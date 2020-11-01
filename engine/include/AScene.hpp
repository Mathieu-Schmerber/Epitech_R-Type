//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ASCENE_HPP
#define RTYPE_ASCENE_HPP

#include <ostream>
#include "ecs/System.hpp"

namespace Engine {

    class AScene : public std::enable_shared_from_this<AScene> {

    protected:
        int _sceneId;
        int _sceneSwitchRequest;
        std::vector<std::unique_ptr<Engine::System>> _systems;
        std::vector<std::shared_ptr<Engine::Entity>> _entities;

    public:
        explicit AScene(int id);
        ~AScene();

        int getId() const;
        void spawnEntity(std::shared_ptr<Entity> entity);
        int getSwitchRequest() const;
        void requestSwitch(int scene);

        virtual void update();
    };

}

#endif //RTYPE_ASCENE_HPP
