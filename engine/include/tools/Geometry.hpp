//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_GEOMETRY_HPP
#define RTYPE_GEOMETRY_HPP

#include <utility>
#include <cmath>

namespace Engine {

    static const double PI = 3.141592653589793238463;

    template<typename T>
    struct Point {
        T x;
        T y;

        bool operator==(const Point &rhs) const {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const Point &rhs) const {
            return rhs != *this;
        }
    };

    template<typename T>
    using Size = struct Point<T>;

    template<typename T>
    using Scale = struct Point<T>;

    template<typename T>
    struct Box {
        T x1;
        T x2;
        T y1;
        T y2;
        Point<T> size;

        Box(T x1, T x2, T y1, T y2) : x1(x1), x2(x2), y1(y1), y2(y2), size({x2 - x1, y2 - y1}){}
        Box(Point<T> pos, Point<T> size) : x1(pos.x), x2(pos.x + size.x), y1(pos.y), y2(pos.y + size.y), size(size) {}

        bool operator==(const Box &rhs) const {
            return x1 == rhs.x1 &&
                   x2 == rhs.x2 &&
                   y1 == rhs.y1 &&
                   y2 == rhs.y2;
        }

        bool operator!=(const Box &rhs) const {
            return rhs != *this;
        }
    };

    class Geometry {
    public:

        static double degreeToRadiant(double degree) {return degree * (PI / 180);}

        template<typename T>
        static Point<T> rotateVector(Engine::Point<T> vector, double degree)
        {
            double angle = degreeToRadiant(degree);
            Point<T> res = {
                    vector.x * cos(angle) - vector.y * sin(angle),
                    vector.x * sin(angle) + vector.y * cos(angle)};

            return res;
        }

        template<typename T>
        static bool doOverlap(const Point<T> &point, const Box<T> &box) {
            return (point.x >= box.x1 && point.x <= box.x2 &&
                    point.y >= box.y1 && point.y <= box.y2);
        }

        template<typename T>
        static bool doOverlap(const Box<T> &box1, const Box<T> &box2) {
            return !((box1.x2 < box2.x1 || box1.x1 > box2.x2) || (box1.y2 < box2.y1 || box1.y1 > box2.y2));
        }
    };
}

#endif //RTYPE_GEOMETRY_HPP
