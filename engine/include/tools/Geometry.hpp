//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_GEOMETRY_HPP
#define RTYPE_GEOMETRY_HPP

#include <cmath>
#include <utility>
#include <cmath>
#include <iostream>

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

        Point<T> operator * (double c) const {
            return Point<T>({x * c, y * c});
        }

        Point<T> operator - (double c) const {
            return Point<T>({x - c, y - c});
        }

        Point<T> operator + (double c) const {
            return Point<T>({x + c, y + c});
        }

        template<typename U>
        explicit operator Point<U>() const {
            return {static_cast<U>(x), static_cast<U>(y)};
        }
    };

    template<typename T>
    using Size = struct Point<T>;

    template<typename T>
    using Scale = struct Point<T>;

    template<typename T>
    using Vector = struct Point<T>;

    template<typename T>
    struct Box {
        T x1;
        T x2;
        T y1;
        T y2;
        Point<T> size;
        Point<T> center;

        /*!
         * \brief Creates a box.
         * \param x1 left
         * \param x2 right
         * \param y1 top
         * \param y2 bottom
        */
        Box(T x1, T x2, T y1, T y2) : x1(x1), x2(x2), y1(y1), y2(y2), size({x2 - x1, y2 - y1}), center({x1 - size.x, y1 - size.y}){}

        /*!
         * \brief Creates a box.
         * \param pos top-left corner
         * \param size width-height
        */
        Box(Point<T> pos, Point<T> size) : x1(pos.x), x2(pos.x + size.x), y1(pos.y), y2(pos.y + size.y), size(size), center({x1 - size.x, y1 - size.y}) {}

        bool operator==(const Box &rhs) const {
            return x1 == rhs.x1 &&
                   x2 == rhs.x2 &&
                   y1 == rhs.y1 &&
                   y2 == rhs.y2;
        }

        bool operator!=(const Box &rhs) const {
            return rhs != *this;
        }

        [[nodiscard]] bool doOverlap(const Box &rhs) const;
        [[nodiscard]] bool doOverlap(const Point<T> &point) const;

    };

    class Geometry {
    public:

        [[nodiscard]] static double degreeToRadiant(double degree) {return degree * (PI / 180);}
        [[nodiscard]] static double radiantToDegree(double rad) {return rad * (180 / PI);}

        template<typename T>
        [[nodiscard]] static Point<T> rotateVector(Engine::Point<T> vector, double degree)
        {
            double angle = degree * PI/180;
            double ca = std::cos(angle);
            double sa = std::sin(angle);

            Point<T> res = {
                    ca * vector.x - sa * vector.y,
                    sa * vector.x + ca * vector.y};

            return res;
        }

        template <typename T>
        static Engine::Vector<T> normalizeVectorScale(Engine::Vector<T> vector, T scale)
        {
            return normalizeVector(vector) * scale;
        }

        template<typename T>
        static Engine::Vector<T> normalizeVector(Engine::Vector<T> vector)
        {
            T magnitude = getVectorMagnitude(vector);

            if (magnitude == 0)
                return vector;
            vector = Vector<T>{vector.x / magnitude, vector.y / magnitude};
            return vector;
        }

        template<typename T>
        [[nodiscard]] static double getVectorMagnitude(const Engine::Point<T> &vector)
        {
            return (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
        }

        template<typename T>
        static T dotProduct(Engine::Vector<T> &a, Engine::Vector<T> &b)
        {
            return a.x * b.x + a.y * b.y;
        }

        template<typename T>
        static double vectorAngle(Engine::Vector<T> a, Engine::Vector<T> b)
        {
            double cosTheta = dotProduct(a, b) / (getVectorMagnitude(a) * getVectorMagnitude(b));

            return radiantToDegree(acos(cosTheta));
        }

        template<typename T>
        static Engine::Vector<T> reflect(Engine::Vector<T> input, Engine::Vector<T> normal)
        {
            return {input.x - 2 * dotProduct(input, normal) * normal.x, input.y - 2 * dotProduct(input, normal) * normal.y};
        }

        template<typename T>
        [[nodiscard]] static double getDistance(const Engine::Point<T> &a, const Engine::Point<T> &b)
        {
            return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
        }

        template<typename T>
        [[nodiscard]] static Vector<T> getVectorNormal(const Vector<T> &ref)
        {
            return normalizeVector(rotateVector(ref, 90));
        }

        template<typename T>
        [[nodiscard]] static Vector<T> getVectorBetween(const Point<T> &a, const Point<T> &b)
        {
            return {b.x - a.x, b.y - a.y};
        }

        template<typename T>
        [[nodiscard]] static Point<T> placeForward(const Box<T> &ref, const Box<T> &a)
        {
            if (ref.size.y > a.size.y)
                return {ref.x2, ref.y1 + (ref.size.y - a.size.y) / 2};
            else
                return {ref.x2, ref.y1 + (a.size.y - ref.size.y) / 2};
        }

        template<typename T>
        [[nodiscard]] static Point<T> placeTop(const Box<T> &ref, const Box<T> &a)
        {
            if (ref.size.x > a.size.x)
                return {ref.x1 + (ref.size.x - a.size.x) / 2, ref.y1 - a.size.y};
            else
                return {ref.x1 + (a.size.x - ref.size.x) / 2, ref.y1 - a.size.y};
        }

        template<typename T>
        [[nodiscard]] static Point<T> placeBottom(const Box<T> &ref, const Box<T> &a)
        {
            if (ref.size.x > a.size.x)
                return {ref.x1 + (ref.size.x - a.size.x) / 2, ref.y1 + a.size.y};
            else
                return {ref.x1 + (a.size.x - ref.size.x) / 2, ref.y1 + a.size.y};
        }

        template<typename T>
        [[nodiscard]] static bool doOverlap(const Point<T> &point, const Box<T> &box) {
            return (point.x >= box.x1 && point.x <= box.x2 &&
                    point.y >= box.y1 && point.y <= box.y2);
        }

        template<typename T>
        [[nodiscard]] static bool doOverlap(const Box<T> &box1, const Box<T> &box2) {
            return (box1.x1 < box2.x1 + box2.size.x &&
                    box1.x1 + box1.size.x > box2.x1 &&
                    box1.y1 < box2.y1 + box2.size.y &&
                    box1.size.y + box1.y1 > box2.y1);
        }

        template<typename T>
        [[nodiscard]] static Vector<T> getCollisionNormal(const Box<T> &box1, const Box<T> &box2) {
            auto dx = (box1.x1 + box1.size.x / 2) - (box2.x1 + box2.size.x / 2);
            auto dy = (box1.y1 + box1.size.y / 2) - (box2.y1 + box2.size.y / 2);
            auto width = (box1.size.x + box2.size.x) / 2;
            auto height = (box1.size.y + box2.size.y) / 2;
            auto crossWidth = width * dy;
            auto crossHeight = height * dx;
            Vector<T> collision = {0, 0};

            if(abs(dx) <= width && abs(dy) <= height) {
                if (crossWidth > crossHeight)
                    collision=(crossWidth > (-crossHeight))? Vector<T>{0, 1} : Vector<T>{-1, 0};
                else
                    collision=(crossWidth > -(crossHeight))? Vector<T>{1, 0} : Vector<T>{0, -1};
            }
            return(collision);
        }
    };
}

template<typename T>
[[nodiscard]] bool Engine::Box<T>::doOverlap(const Box<T> &rhs) const {
    return Geometry::doOverlap(rhs, this);
}

template<typename T>
[[nodiscard]] bool Engine::Box<T>::doOverlap(const Engine::Point<T> &point) const
{
    return Geometry::doOverlap(point, this);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Engine::Box<T>& box)
{
    os << "x1;x2: " << box.x1 << ";" << box.x2 << " && ";
    os << "y1;y2: " << box.y1 << ";" << box.y2;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Engine::Vector<T>& vector)
{
    os << "x1;x2: " << vector.x << ";" << vector.y;
    return os;
}

template <typename T>
Engine::Point<T> operator + (Engine::Vector<T> a, Engine::Vector<T> b) {
    return Engine::Point<T>({a.x + b.x, a.y + b.y});
}

template <typename T>
Engine::Point<T> operator - (Engine::Vector<T> a, Engine::Vector<T> b) {
    return Engine::Point<T>({a.x - b.x, a.y - b.y});
}

template <typename T>
Engine::Vector<T> operator * (Engine::Vector<T> a, Engine::Vector<T> b) {
    return Engine::Vector<T>({a.x * b.x, a.y * b.y});
}

#endif //RTYPE_GEOMETRY_HPP
