/*!
 * @file TextureSFML.hpp
 * @brief Manage SFML's texture
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
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
    /*!
     * \brief Texture SFML constructor with filename
     * \param filename filename to find the texture
     *
     * Create a texture by loading it from a file
    */
    explicit TextureSFML(const std::string& filename) : Engine::ATexture(filename), _texture(std::make_shared<sf::Texture>()) {
        loadFromFile(filename);
    }
    virtual ~TextureSFML() { std::cout << "destroy TextureSFML" << std::endl; }
    void loadFromFile(std::string filename) final;
    std::shared_ptr<sf::Texture> &getTexture();

};


#endif //RTYPE_TEXTURESFML_HPP
