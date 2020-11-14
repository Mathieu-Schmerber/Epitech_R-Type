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
#include "entities/Enemy.hpp"

namespace Engine {

    class DynamicLibManager {
    private:
        std::vector<Engine::ADLLoader *> _libs;

    public:
        template<typename T>
        void loadNewLib(std::string libName)
        {
            if (!libStocked(libName))
                _libs.push_back(new DLLoader<T>(libName));
        }

        template<typename T>
        T *getInstance(std::string libName)
        {
            auto it = std::find_if(_libs.begin(), _libs.end(), [&](auto l) { return l->getLibName() == libName; });

            if (it != _libs.end()) {
                try {
                    return dynamic_cast<DLLoader<T> *>(*it)->getInstance();
                } catch (EngineException &e) {
                    std::cerr << e << std::endl;
                    throw EngineException("DynamicLibManager", "Unable to get instance for lib " + libName);
                }
            }
            throw EngineException("DynamicLibManager", "Lib not registered");
        }

        bool libStocked(std::string libName)
        {
            auto it = std::find_if(_libs.begin(), _libs.end(), [&](auto l) { return l->getLibName() == libName; });

            return it != _libs.end();
        }
    };
}
#endif //RTYPE_DYNAMICLIBMANAGER_HPP
