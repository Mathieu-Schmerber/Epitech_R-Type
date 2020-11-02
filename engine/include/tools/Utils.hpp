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

namespace Engine {
    class Utils {
    public:
        template<typename T>
        static void removeFromVector(std::vector<T> &vector, T item)
        {
            vector.erase(std::remove_if(vector.begin(), vector.end(), [item](T x){return x == item;}));
        }

        template<typename T>
        static bool isInVector(std::vector<T> &vector, T item)
        {
            return (std::find_if(vector.begin(), vector.end(), [item](T x){return x == item;}) != vector.end());
        }

        template<typename T, typename U>
        static std::map<U, T> reverseMap(std::map<T, U> map)
        {
            std::map<U, T> rv;

            for (auto &e : map)
                rv[e.second] = e.first;
            return rv;
        }

        template<class T>
        static std::unique_ptr<T> copyUnique(const std::unique_ptr<T> &source)
        {
            return (source ? std::make_unique<T>(*source) : nullptr);
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

#endif //RTYPE_UTILS_HPP
