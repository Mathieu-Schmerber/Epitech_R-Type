//
// Created by mathi on 09/11/2020.
//

#ifndef RTYPE_BUTTONSYSTEM_HPP
#define RTYPE_BUTTONSYSTEM_HPP

#include "ecs/System.hpp"
#include "graphical/AEvents.hpp"

namespace Engine {

    class ButtonSystem : public Engine::System {
    public:
        explicit ButtonSystem();

        void update() override;
    };
}


#endif //RTYPE_BUTTONSYSTEM_HPP
