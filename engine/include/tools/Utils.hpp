/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#ifndef RTYPE_UTILS_HPP
#define RTYPE_UTILS_HPP

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <string>
#include <iostream>
#include <functional>

namespace Engine {
    class Utils {
    public:
        template<typename T>
        static void removeFromVector(std::vector<T> &vector, T item)
        {
            if (isInVector(vector, item))
                vector.erase(std::remove_if(vector.begin(), vector.end(), [item](T x){return x == item;}));
        }

        template<typename T>
        [[nodiscard]] static bool isInVector(std::vector<T> &vector, T item)
        {
            return (std::find_if(vector.begin(), vector.end(), [item](T x){return x == item;}) != vector.end());
        }

        template<typename T>
        [[nodiscard]] static T getInVector(std::vector<T> &vector, T item)
        {
            return *(std::find_if(vector.begin(), vector.end(), [item](T x){return x == item;}));
        }

        template<typename T>
        [[nodiscard]] static bool isInVectorCpy(std::vector<T> vector, T item)
        {
            return (std::find_if(vector.begin(), vector.end(), [item](T x){return x == item;}) != vector.end());
        }

        template<typename T, typename U>
        [[nodiscard]] static bool isInMap(std::map<T, U> &map, T item)
        {
            return (map.find(item) != map.end());
        }

        template<typename T, typename U>
        [[nodiscard]] static std::map<U, T> reverseMap(std::map<T, U> map)
        {
            std::map<U, T> rv;

            for (auto &e : map)
                rv[e.second] = e.first;
            return rv;
        }

        template<class T>
        [[nodiscard]] static std::unique_ptr<T> copyUnique(const std::unique_ptr<T> &source)
        {
            return (source ? std::make_unique<T>(*source) : nullptr);
        }

        static void printIntTab(const std::string &prefix, const std::vector<int> &tab) {
            std::cout << prefix << std::endl;
            std::cout << "=> ";
            for (auto &i : tab)
                std::cout << i << " ";
            std::cout << std::endl;
        }

        template <typename T>
        static bool isInVector(std::vector<T> vector, std::function<bool (T)>(condition))
        {
            return (std::find_if(vector.begin(), vector.end(), condition) != vector.end());
        }

        template<typename T>
        static void removeFromVector(std::vector<T> &vector, std::function<bool (T)>(condition))
        {
            if (isInVector(vector, condition))
                vector.erase(std::remove_if(vector.begin(), vector.end(), condition));
        }

        template <typename T>
        static T getInVector(std::vector<T> vector, std::function<bool (T)>(condition))
        {
            return *(std::find_if(vector.begin(), vector.end(), condition));
        }

    };
}

template<typename T>
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &c, std::vector<T> vector)
{
    for (auto &i : vector)
        c << i << " ";
    return c;
}

template<typename T>
std::vector<T> operator += (std::vector<T> &a, std::vector<T> &b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

#endif //RTYPE_UTILS_HPP
