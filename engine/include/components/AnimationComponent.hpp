//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_ANIMATIONCOMPONENT_HPP
#define RTYPE_ANIMATIONCOMPONENT_HPP

#include <map>
#include "ecs/Component.hpp"
#include "graphical/ASprite.hpp"
#include "tools/Utils.hpp"

namespace Engine {

    class AnimationComponent : public Engine::Component
    {
    private:
        std::map<std::string, std::vector<Box<int>>> _animations;
        size_t _frame;
        std::string _current;

    public:
        explicit AnimationComponent() : _animations({}), _frame(0), Engine::Component() {}
        explicit AnimationComponent(const std::map<std::string, std::vector<Box<int>>> &anim)
        : _animations(anim), _frame(0), Engine::Component() {
            if (!anim.empty())
                this->_current = anim.begin()->first;
        }

        bool hasAnimations() const {return !(this->_animations.empty());}

        void addAnimation(const std::string &name, const std::vector<Box<int>> &frames) {
            if (Utils::isInMap(this->_animations, name))
                std::cerr << "\033[33mAnimation WARNING : adding an already existing animation name, will overwrite its content (" << name <<")\033[0m" << std::endl;
            this->_animations[name] = frames;
        }

        void setAnimation(const std::string &name) {
            if (Utils::isInMap(this->_animations, name)) {
                this->_current = name;
                this->_frame = 0;
            }
        }

        Box<int> getNextFrame() {
            Box<int> res(0, 0, 0, 0);

            if (Utils::isInMap(this->_animations, this->_current) && !this->_animations[_current].empty()) {
                this->_frame++;
                if (this->_frame >= this->_animations[_current].size())
                    this->_frame = 0;
                res = this->_animations[_current].at(this->_frame);
            }
            return res;
        }
    };
}

#endif //RTYPE_ANIMATIONCOMPONENT_HPP