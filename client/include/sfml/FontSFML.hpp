/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_FONTSFML_HPP
#define RTYPE_FONTSFML_HPP

#include "graphical/AFont.hpp"
#include <SFML/Graphics/Font.hpp>

class FontSFML : public Engine::AFont {
private:
    sf::Font _font;
    std::string _fileName;

public:
    FontSFML() = delete;
    explicit FontSFML(std::string fileName) : Engine::AFont() {
        loadFromFile(std::move(fileName));
        _fileName = fileName;
    }
    void loadFromFile(std::string file) final;
    sf::Font &getFont() {return _font;};
    [[nodiscard]] std::string getFileName() const final;
};


#endif //RTYPE_FONTSFML_HPP
