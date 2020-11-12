//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_WINDOWRESIZESYSTEM_HPP
#define RTYPE_WINDOWRESIZESYSTEM_HPP

#include "ecs/System.hpp"
#include "tools/Geometry.hpp"
#include "graphical/AWindow.hpp"

namespace Engine {

    class WindowResizeSystem : public Engine::System
    {
    private:
        Size<float> _lastSize;
        Size<float> _baseSize;
        std::shared_ptr<AWindow> _window;
    public:
        WindowResizeSystem(std::shared_ptr<AWindow> &window);
        void update() override;
    };

}

#endif //RTYPE_WINDOWRESIZESYSTEM_HPP
