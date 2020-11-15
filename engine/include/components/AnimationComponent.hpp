//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_ANIMATIONCOMPONENT_HPP
#define RTYPE_ANIMATIONCOMPONENT_HPP

#include <map>
#include <chrono>
#include "ecs/Component.hpp"
#include "graphical/ASprite.hpp"
#include "tools/Utils.hpp"

namespace Engine {

    /*!
     * @brief This component stores all the data needed to animate a sprite.
     */
    class AnimationComponent : public Engine::Component
    {
    private:
        std::chrono::high_resolution_clock::time_point _last;
        std::map<int, std::vector<Box<double>>> _animations;
        size_t _frame;
        double _frameTime;
        int _current;
        bool _looping;

    public:
        /*!
         * @brief Default constructor.
         */
        explicit AnimationComponent() : _animations({}), _frame(0), _current(-1), _frameTime(0), _looping(false),
                                        _last(std::chrono::high_resolution_clock::now()), Engine::Component()
                                        {}
        /*!
         * @param animationTime Time per frame
         * @param anim Map of frames
         * @param looping Does the animation loop
         */
        explicit AnimationComponent(double animationTime, const std::map<int, std::vector<Box<double>>> &anim = {}, bool looping = false)
                                    : _animations(anim), _frame(0), _current(-1), _frameTime(animationTime), _looping(looping),
                                    _last(std::chrono::high_resolution_clock::now()), Engine::Component() {
            if (!anim.empty())
                this->_current = anim.begin()->first;
        }

        [[nodiscard]] bool hasAnimations() const {return !(this->_animations.empty());}

        [[nodiscard]] double getFrameTime() const {return this->_frameTime;}

        [[nodiscard]]  std::chrono::high_resolution_clock::time_point getLastRefresh() {return this->_last;};

        [[nodiscard]] bool isLooping() const {return this->_looping;}

        /*!
         * @brief Refresh animation timer.
         */
        void refresh() {this->_last = std::chrono::high_resolution_clock::now();}

        void setFrameTime(double frameTime) {this->_frameTime = frameTime;}

        /*!
         * @brief Add an animation.
         * @param name Name of the animation
         * @param frames List of animation's frames
         */
        void addAnimation(int name, const std::vector<Box<double>> &frames) {
            if (Utils::isInMap(this->_animations, name))
                std::cerr << "\033[33mAnimation WARNING : adding an already existing animation name, will overwrite its content (" << name <<")\033[0m" << std::endl;
            this->_animations[name] = frames;
        }

        /*!
         * @brief Plays an animation.
         * @param name Name of the animation
         * @param loop Does the animation loop
         */
        void setAnimation(int name, bool loop = true) {
            if (Utils::isInMap(this->_animations, name) && this->_current != name) {
                this->refresh();
                this->_current = name;
                this->_looping = loop;
                this->_frame = 0;
            }
        }

        Box<double> getNextFrame() {
            Box<double> res(0, 0, 0, 0);

            if (Utils::isInMap(this->_animations, this->_current) && !this->_animations[_current].empty()) {
                this->_frame++;
                if (this->_frame >= this->_animations[_current].size() && this->_looping)
                    this->_frame = 0;
                else if (this->_frame >= this->_animations[_current].size() && !this->_looping)
                    this->_frame = this->_animations[_current].size() - 1;
                res = this->_animations[_current].at(this->_frame);
            }
            return res;
        }

        [[nodiscard]] int getAnimation() const {
            return _current;
        }
    };
}

#endif //RTYPE_ANIMATIONCOMPONENT_HPP