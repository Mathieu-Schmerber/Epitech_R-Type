/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <string>
#include "ADLLoader.hpp"
#include <iostream>
#include "tools/EngineExceptions.hpp"

#ifdef __unix__

#include <dlfcn.h>

#elif defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#endif

namespace Engine {

    template<typename T>
    class DLLoader : public Engine::ADLLoader {
    public:
        explicit DLLoader(const std::string &libName);

        ~DLLoader() override
        { std::cout << "Lib destroyed" << std::endl; }

        typedef T *(*fct)();

        void open();

        T *getInstance() const;

        void close(T instance) const;

    private:
        void *_lib;
    };

    template<typename T>
    DLLoader<T>::DLLoader(const std::string &libName) : _lib(nullptr), ADLLoader(libName)
    {
        try {
            open();
        } catch (Engine::EngineException &e) {
            std::cerr << e << std::endl;
        }
    }

    template<typename T>
    void DLLoader<T>::open()
    {
        #ifdef __unix__
        _lib = dlopen(_libName.c_str(), RTLD_LAZY);
        if (!_lib)
            std::cerr << dlerror() << std::endl;
        #elif defined(_WIN32) || defined(WIN32)
        _lib = LoadLibrary(TEXT(_libName.c_str()));
        #endif
        if (!_lib)
            throw Engine::DynamicLibError("Invalid open lib: " + _libName);
    }

    template<typename T>
    T *DLLoader<T>::getInstance() const
    {
        if (!_lib)
            throw Engine::DynamicLibError("Lib Not loaded");

        #ifdef __unix__
        if (!dlsym(_lib, "newInstance"))
            throw Engine::DynamicLibError("Unable to load function \"newInstance\"");
        T *(*f)();
        *(void **) (&f) = dlsym(_lib, "newInstance");
        return ((*f)());
        #elif defined(_WIN32) || defined(WIN32)
        if (!static_cast<void *>(GetProcAddress(static_cast<HINSTANCE>(_lib), "newInstance")))
            throw Engine::DynamicLibError("Unable to load function \"newInstance\"");
        fct f = (fct) GetProcAddress(static_cast<HINSTANCE>(_lib), "newInstance");
        return ((f)());
        #endif
    }

    template<typename T>
    void DLLoader<T>::close(T instance) const
    {
        std::cout << "lib closed" << std::endl;
        if (!_lib)
            return;
        #ifdef __unix__
        if (!dlsym(_lib, "destroyInstance"))
            throw std::exception();
        T (*f)(T);
        *(void **) (&f) = dlsym(_lib, "destroyInstance");
        ((*f)(instance));
        dlclose(_lib);
        #elif defined(_WIN32) || defined(WIN32)
        FreeLibrary(_lib);
        #endif
    }
}

#if defined(_WIN32) || defined(WIN32)
#undef _WIN32_WINNT
#endif

#endif //RTYPE_DLLOADER_HPP
