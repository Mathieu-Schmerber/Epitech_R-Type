/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "DataFont.hpp"

std::string DataFont::getFileName() const
{
    return _fileName;
}

void DataFont::loadFromFile(std::string fileName)
{
    _fileName = fileName;
}