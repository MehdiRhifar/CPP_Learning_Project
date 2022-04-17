#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <typename Type, const unsigned int Dimension,
    typename  = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>

struct Point{
    std::array<Type, Dimension> values;

    Point() = default;

    Point(Type x, Type y) : values { x, y } { static_assert(Dimension == 2); }

    Point(Type x, Type y, Type z) : values { x, y, z } { static_assert(Dimension == 3); }

    template <typename... Args>
    Point(const Type&& first, const Args&&... args) : values { first, std::forward<Type>( static_cast<Type>(args) )... }
    {
        static_assert(sizeof...(args) + 1 == Dimension,"Don't have good number of argument for constructor");
    }

    template <int i>
    Type& get() { return values[i]; }

    template <int i>
    Type get() const { return values[i]; }


    float& x() {
        static_assert(Dimension > 0, "Dimension too low to call x()");
        return values[0];
    }

    float x() const {
        static_assert(Dimension > 0, "Dimension too low to call x()");
        return values[0];
    }

    float& y() {
        static_assert(Dimension > 1, "Dimension too low to call y()");
        return values[1];
    }
    float y() const {
        static_assert(Dimension > 1, "Dimension too low to call y()");
        return values[1];
    }

    float& z() {
        static_assert(Dimension > 2, "Dimension too low to call z()");
        return values[2];
    }
    float z() const {
        static_assert(Dimension > 2, "Dimension too low to call z()");
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::plus<float>());
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<float>());
        return *this;
    }

        Point& operator*=(const Point& other)
        {
            x() *= other.x();
            y() *= other.y();
            return *this;
        }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](float v) { return v * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point<Type, Dimension>& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const Point<Type, Dimension>& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const float scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const {
        Point p = *this;
        std::transform(p.values.begin(), p.values.end(), p.values.begin(), [](Type elem) { return - elem; });
        return p;
    }

    float length() const {  return std::sqrt(std::reduce(values.begin(), values.end(), 0.0,
                                     [](float acc, float cur) { return acc + (cur * cur); })); }

    float distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    const std::string toString() {
        std::string s;
        return std::accumulate(values.begin(), values.end(), s,
                                         [](std::string& acc, const Type& cur) { return acc + (acc.empty() ? "" : ",") +std::to_string(cur); });
    }
};

template <typename Type, const unsigned int Dimension>
std::ostream & operator <<( std::ostream &os, Point<Type, Dimension> point)
{
    return os << point.toString();
}


using Point2D = Point<float, 2>;
using Point3D = Point<float, 3>;

//struct Point2D
//{
//    float values[2] {};
//
//    Point2D() {}
//    Point2D(float x, float y) : values { x, y } {}
//
//    float& x() { return values[0]; }
//    float x() const { return values[0]; }
//
//    float& y() { return values[1]; }
//    float y() const { return values[1]; }
//
//    Point2D& operator+=(const Point2D& other)
//    {
//        x() += other.x();
//        y() += other.y();
//        return *this;
//    }
//
//    Point2D& operator*=(const Point2D& other)
//    {
//        x() *= other.x();
//        y() *= other.y();
//        return *this;
//    }
//
//    Point2D& operator*=(const float scalar)
//    {
//        x() *= scalar;
//        y() *= scalar;
//        return *this;
//    }
//
//    Point2D operator+(const Point2D& other) const
//    {
//        Point2D result = *this;
//        result += other;
//        return result;
//    }
//
//    Point2D operator*(const Point2D& other) const
//    {
//        Point2D result = *this;
//        result *= other;
//        return result;
//    }
//
//    Point2D operator*(const float scalar) const
//    {
//        Point2D result = *this;
//        result *= scalar;
//        return result;
//    }
//};

//struct Point3D
//{
//    std::array<float, 3> values;
//
//    Point3D() {}
//    Point3D(float x, float y, float z) : values { x, y, z } {}
//
//    float& x() { return values[0]; }
//    float x() const { return values[0]; }
//
//    float& y() { return values[1]; }
//    float y() const { return values[1]; }
//
//    float& z() { return values[2]; }
//    float z() const { return values[2]; }
//
//    Point3D& operator+=(const Point3D& other)
//    {
//        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
//                       std::plus<float>());
//        return *this;
//    }
//
//    Point3D& operator-=(const Point3D& other)
//    {
//        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
//                       std::minus<float>());
//        return *this;
//    }
//
//    Point3D& operator*=(const float scalar)
//    {
//        std::transform(values.begin(), values.end(), values.begin(),
//                       [scalar](float v) { return v * scalar; });
//        return *this;
//    }
//
//    Point3D operator+(const Point3D& other) const
//    {
//        Point3D result = *this;
//        result += other;
//        return result;
//    }
//
//    Point3D operator-(const Point3D& other) const
//    {
//        Point3D result = *this;
//        result -= other;
//        return result;
//    }
//
//    Point3D operator*(const float scalar) const
//    {
//        Point3D result = *this;
//        result *= scalar;
//        return result;
//    }
//
//    Point3D operator-() const { return Point3D { -x(), -y(), -z() }; }
//
//    float length() const {  return std::sqrt(std::reduce(values.begin(), values.end(), 0.0,
//                                     [](float acc, float cur) { return acc + (cur * cur); })); }
//
//    float distance_to(const Point3D& other) const { return (*this - other).length(); }
//
//    Point3D& normalize(const float target_len = 1.0f)
//    {
//        const float current_len = length();
//        if (current_len == 0)
//        {
//            throw std::logic_error("cannot normalize vector of length 0");
//        }
//
//        *this *= (target_len / current_len);
//        return *this;
//    }
//
//    Point3D& cap_length(const float max_len)
//    {
//        assert(max_len > 0);
//
//        const float current_len = length();
//        if (current_len > max_len)
//        {
//            *this *= (max_len / current_len);
//        }
//
//        return *this;
//    }
//
//    const std::string toString() {
//        return std::to_string(x()) + ", " + std::to_string(y()) + ", " + std::to_string(z());
//    }
//};

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
