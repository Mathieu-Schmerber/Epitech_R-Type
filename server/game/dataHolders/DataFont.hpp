/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_DATAFONT_HPP
#define RTYPE_DATAFONT_HPP

#include <utility>
#include "graphical/AFont.hpp"

class DataFont : public Engine::AFont {
private:
    std::string _fileName;

public:
    DataFont() = default;
    explicit DataFont(std::string fileName) : _fileName(std::move(fileName)), Engine::AFont() {}

    [[nodiscard]] std::string getFileName() const final;
    void loadFromFile(std::string fileName) final;
};

#endif //RTYPE_DATAFONT_HPP
