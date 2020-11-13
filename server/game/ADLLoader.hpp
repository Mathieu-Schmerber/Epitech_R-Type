/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ADLLOADER_HPP
#define RTYPE_ADLLOADER_HPP

class ADLLoader {
protected:
    std::string _libName;

public:
    ADLLoader(std::string libName) : _libName(libName) {}
    virtual ~ADLLoader() = default;
    [[nodiscard]] std::string getLibName() const {return _libName;};
};


#endif //RTYPE_ADLLOADER_HPP
