//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ASCENE_HPP
#define RTYPE_ASCENE_HPP

#include "ecs/System.hpp"

namespace Engine {

    class AScene {

    protected:
        int _sceneId;
        std::vector<std::unique_ptr<Engine::System>> _systems;
        std::vector<std::reference_wrapper<std::unique_ptr<Engine::Entity>>> _entities;

    public:
        explicit AScene(int id);
        ~AScene();

        int getId() const;

        virtual void spawnEntity(std::unique_ptr<Entity> &entity);
        virtual void init();  // push entities to systems
        virtual void update(); // calls systems update( );
    };

}

#endif //RTYPE_ASCENE_HPP
