/*!
 * @file GraphicalSFML.hpp
 * @brief Manage SFML's graphical window, sound and events
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
*/


#ifndef RTYPE_GRAPHICALSFML_HPP
#define RTYPE_GRAPHICALSFML_HPP

#include <graphical/AGraphical.hpp>
#include <graphical/AWindow.hpp>
#include <graphical/ASound.hpp>
#include <graphical/AEvents.hpp>
#include <memory>

class GraphicalSFML : public Engine::AGraphical {
public:
    /*!
     * \brief EventsSFML default constructor
     *
    */
    GraphicalSFML() = default;
    /*!
     * \brief EventsSFML default constructor
     * \param window a Awindow shared_ptr
     * \param sound a ASound shared_ptr
     * \param events a AEvents shared_ptr
     *
    */
    GraphicalSFML(std::unique_ptr<Engine::AWindow> window, std::unique_ptr<Engine::ASound> sound, std::unique_ptr<Engine::AEvents> events) :
    Engine::AGraphical(std::move(window), std::move(sound), std::move(events)) {};
};


#endif //RTYPE_GRAPHICALSFML_HPP
