//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_TEXTSYSTEM_HPP
#define RTYPE_TEXTSYSTEM_HPP

#include "graphical/AWindow.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class TextSystem : public Engine::System {

    private:
        std::shared_ptr<Engine::AWindow> _window;

        [[nodiscard]] static bool compare(const std::shared_ptr<Engine::Entity> &a, const std::shared_ptr<Engine::Entity> &b);
    public:
        explicit TextSystem(std::shared_ptr<Engine::AWindow> &window);
        void update() override;
    };

}
#endif //RTYPE_TEXTSYSTEM_HPP
