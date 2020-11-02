//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_ANIMATIONSYSTEM_HPP
#define RTYPE_ANIMATIONSYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {

    class AnimationSystem : public Engine::System
    {
    public:
        AnimationSystem();
        void update() override;
    };

}


#endif //RTYPE_ANIMATIONSYSTEM_HPP
