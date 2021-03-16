#ifndef __VECTOR_MATH_HPP__
#define __VECTOR_MATH_HPP__
#include <initializer_list>
#include <ostream>
#include <cmath>
#include <type_traits>

template<typename T> concept C1 = std::is_same<T, float>::value || std::is_same<T, double>::value;

template<C1 T>
class _Vec2 {
public:
    _Vec2(T x, T y) noexcept : x(x), y(y) {}
    _Vec2(std::initializer_list<T> list) noexcept : x(*list.begin()), y(*(list.begin() + 1)) {}
    template<C1 E>
    _Vec2(const _Vec2<E>& v) noexcept : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
    template<C1 E>
    _Vec2<T>& operator=(const _Vec2<E>& v) noexcept {
        x = static_cast<T>(v.x);
        y = static_cast<T>(v.y);
        return *this;
    }
    _Vec2<T>& operator+=(const _Vec2<T>& v) noexcept {
        x += v.x;
        y += v.y;
        return *this;
    }
    _Vec2<T>& operator-=(const _Vec2<T>& v) noexcept {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    _Vec2<T> operator+(const _Vec2<T>& v) noexcept {
        return _Vec2(*this).operator+=(v);
    }
    _Vec2<T> operator-(const _Vec2<T>& v) noexcept {
        return _Vec2(*this).operator-=(v);
    }
    _Vec2<T>& operator*=(T s) noexcept {
        x *= s;
        y *= s;
        return *this;
    }
    _Vec2<T>& operator/=(T s) noexcept {
        x /= s;
        y /= s;
        return *this;
    }
    _Vec2<T> operator*(T s) noexcept {
        return _Vec2(*this).operator*=(s);
    }
    _Vec2<T> operator/(T s) noexcept {
        return _Vec2(*this).operator/=(s);
    }
    bool operator==(const _Vec2<T>& v) const noexcept {
        return x == v.x && y == v.y;
    }
    bool operator!=(const _Vec2<T>& v) const noexcept {
        return x != v.x || y != v.y;
    }

    const T& GetX() const noexcept {
        return x;
    }
    const T& GetY() const noexcept {
        return y;
    }
    T Magnitude() const noexcept {
        return std::sqrt((x * x) + (y * y));
    }
    void Normalise() noexcept {
        T length = Magnitude();
        x /= length;
        y /= length;
    }
    template<C1 E>
    void Rotate(E angle) noexcept {
        T sine = std::sin(angle);
        T cosine = std::cos(angle);
        
        T old_x = x, old_y = y;
        
        x = old_x * cosine - old_y * sine;
        y = old_x * sine + old_y * cosine;
    }

    friend std::ostream& operator<<(std::ostream& out, const _Vec2<T>& v){
        return out << v.x << " " << v.y << std::endl;
    }
private:
    T x;
    T y;
};

typedef _Vec2<float> Vec2;
#endif