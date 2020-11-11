/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TEXTURESFML_HPP
#define RTYPE_TEXTURESFML_HPP

#include "graphical/ATexture.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>

class TextureSFML : public Engine::ATexture {

private:
    std::shared_ptr<sf::Texture> _texture;

public:
    explicit TextureSFML(const std::string& filename) : Engine::ATexture(filename), _texture(std::make_shared<sf::Texture>()) {
        loadFromFile(filename);
    }
    void loadFromFile(std::string filename) final;
    std::shared_ptr<sf::Texture> &getTexture();

};


#endif //RTYPE_TEXTURESFML_HPP
