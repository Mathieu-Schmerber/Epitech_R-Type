/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <string>
#include <dlfcn.h>

template <typename T>
class DLLoader {
public:
    explicit DLLoader(const std::string& lib);
    void open();
    T getInstance() const;
    void close(T instance) const;
    std::string getLibName() const;
private:
    void *_lib;
    std::string _libName;
};

template<typename T>
DLLoader<T>::DLLoader(const std::string& lib) : _lib(nullptr)
{
    _libName = lib;
}

template<typename T>
void DLLoader<T>::open()
{
    _lib = dlopen(_libName.c_str(), RTLD_LAZY);
    if (!_lib)
        throw std::exception(); //TODO: Utiliser dlerror() !
}

template<typename T>
T DLLoader<T>::getInstance() const
{
    if (!_lib)
        return (nullptr);
    if (!dlsym(_lib, "newInstance"))
        throw std::exception();
    T (*f)();
    *(void **)(&f) = dlsym(_lib, "newInstance");
    return ((*f)());
}

template<typename T>
void DLLoader<T>::close(T instance) const
{
    if (!_lib)
        return;
    if (!dlsym(_lib, "destroyInstance"))
        throw std::exception();
    T (*f)(T);
    *(void **)(&f) = dlsym(_lib, "destroyInstance");
    ((*f)(instance));
    dlclose(_lib);
}

template<typename T>
std::string DLLoader<T>::getLibName() const
{
    return _libName;
}

#endif //RTYPE_DLLOADER_HPP
