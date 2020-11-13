/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_DYNAMICLIBMANAGER_HPP
#define RTYPE_DYNAMICLIBMANAGER_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include "DLLoader.hpp"

class DynamicLibManager {
private:
    std::vector<ADLLoader *> _libs;

public:
    template<typename T>
    void loadNewLib(std::string libName) {
        if (!libStocked(libName))
            _libs.push_back(new DLLoader<T>(libName));
    }

    template<typename T>
    T *getInstance(std::string libName) {
        auto it = std::find_if(_libs.begin(), _libs.end(), [&](auto l) {return l->getLibName() == libName;});

        if (it != _libs.end())
            return dynamic_cast<DLLoader<T> *>(*it)->getInstance();
        throw std::exception();
    }

    bool libStocked(std::string libName) {
        auto it = std::find_if(_libs.begin(), _libs.end(), [&](auto l) {return l->getLibName() == libName;});

        return it != _libs.end();
    }
};


#endif //RTYPE_DYNAMICLIBMANAGER_HPP
