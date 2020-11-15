/*!
 * @file EventsSFML.hpp
 * @brief Manage SFML's events
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
*/


#ifndef RTYPE_EVENTSSFML_HPP
#define RTYPE_EVENTSSFML_HPP

#include "graphical/AEvents.hpp"
#include "sfml/WindowSFML.hpp"
#include <SFML/Window/Event.hpp>
#include "tools/Utils.hpp"
#include <map>


class EventsSFML : public Engine::AEvents {
public:
    /*!
     * \brief EventsSFML constructor
     * \param window window to be stored as reference
     *
     * Create the EventsSFML module
    */
    EventsSFML(std::shared_ptr<Engine::AWindow> &window) : Engine::AEvents(), _window(std::dynamic_pointer_cast<WindowSFML>(window)),
    _mouseRvLink(Engine::Utils::reverseMap(_mouseLink)) {}
    /*!
     * \brief update
     *
     * Update the _event private variable with the pressed, released, clicked [...] events
    */
    void update() override;

    bool isButtonPressed(Engine::Mouse button) override;
    Engine::Point<int> getMousePosDesktopRelative() override;


private:
    std::shared_ptr<WindowSFML> _window;
    sf::Event _event;

    std::map<sf::Mouse::Button, Engine::Mouse> _mouseLink = {
            {sf::Mouse::Right, Engine::Mouse::right},
            {sf::Mouse::Left, Engine::Mouse::left},
            {sf::Mouse::Middle, Engine::Mouse::middle},
            {sf::Mouse::XButton1, Engine::Mouse::extra1},
            {sf::Mouse::XButton2, Engine::Mouse::extra2}
    };
    std::map<Engine::Mouse, sf::Mouse::Button> _mouseRvLink;

    void manageEvents();
};



#endif //RTYPE_EVENTSSFML_HPP
