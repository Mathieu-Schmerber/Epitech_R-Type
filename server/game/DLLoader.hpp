/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <string>

#ifdef __unix__
    #include <dlfcn.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <stdio.h>
#endif

template <typename T>
class DLLoader {
public:
    DLLoader(std::string libName);

    typedef T *(*fct)();

    void open();
    T *getInstance() const;
    void close(T instance) const;
    std::string getLibName() const;
private:
    void *_lib;
    std::string _libName;
};

template<typename T>
DLLoader<T>::DLLoader(const std::string libName) : _lib(nullptr), _libName(libName)
{}

template<typename T>
void DLLoader<T>::open()
{
    #ifdef __unix__
        _lib = dlopen(_libName.c_str(), RTLD_LAZY);
    #elif defined(_WIN32) || defined(WIN32)
        _lib = LoadLibrary(TEXT(_libName.c_str()));
    #endif
    if (!_lib) {
        std::cerr << dlerror() << std::endl;
        throw std::exception();
    }
}

template<typename T>
T *DLLoader<T>::getInstance() const
{
    if (!_lib) {
        std::cerr << "Lib not found" << std::endl;
        return (nullptr);
    }

    #ifdef __unix__
    if (!dlsym(_lib, "newInstance"))
        throw std::exception();
    T *(*f)();
    *(void **)(&f) = dlsym(_lib, "newInstance");
    return ((*f)());
    #elif defined(_WIN32) || defined(WIN32)
    if (!static_cast<void *>(GetProcAddress(static_cast<HINSTANCE>(_lib), "newInstance")))
        throw std::exception();
    fct f = (fct) GetProcAddress(static_cast<HINSTANCE>(_lib), "newInstance");
    return ((f)());
    #endif
}

template<typename T>
void DLLoader<T>::close(T instance) const
{
    if (!_lib)
        return;
    #ifdef __unix__
    if (!dlsym(_lib, "destroyInstance"))
        throw std::exception();
    T (*f)(T);
    *(void **)(&f) = dlsym(_lib, "destroyInstance");
    ((*f)(instance));
    dlclose(_lib);
    #elif defined(_WIN32) || defined(WIN32)
    // TODO
    #endif
}

template<typename T>
std::string DLLoader<T>::getLibName() const
{
    return _libName;
}

#endif //RTYPE_DLLOADER_HPP
