/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/FontSFML.hpp"

void FontSFML::loadFromFile(std::string fileName)
{
    _font.loadFromFile(fileName);
    _fileName = fileName;
}

std::string FontSFML::getFileName() const
{
    return _fileName;
}
