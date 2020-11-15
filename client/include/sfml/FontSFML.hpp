/*!
 * @file FontSFML.hpp
 * @brief Manage SFML's font
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
*/


#ifndef RTYPE_FONTSFML_HPP
#define RTYPE_FONTSFML_HPP

#include "graphical/AFont.hpp"
#include <SFML/Graphics/Font.hpp>

class FontSFML : public Engine::AFont {
private:
    sf::Font _font;

public:
    /*!
     * \brief EventsSFML copy constructor
     *
     * Security call to delete c++ function when the use try to copy the font
    */
    FontSFML() = delete;
    /*!
     * \brief EventsSFML constructor
     * \param filename name of the file which contain the font
     *
     * Create the font as an sf::Font
    */
    explicit FontSFML(std::string fileName) : Engine::AFont() {
        loadFromFile(std::move(fileName));
    }
    void loadFromFile(std::string file) final;
    sf::Font &getFont() {return _font;};
};


#endif //RTYPE_FONTSFML_HPP
