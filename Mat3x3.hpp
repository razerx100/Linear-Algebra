#ifndef __MATRIX_3X3_HPP__
#define __MATRIX_3X3_HPP__
#include <initializer_list>
#include <ostream>
#include "Vector.hpp"


template<typename T> concept flot = std::is_same<T, float>::value || std::is_same<T, double>::value;

template<flot T>
class _Mat3x3 {
public:
    _Mat3x3() noexcept {
        for(int i = 0; i < 9; i++)
            values[i] = 0;
    }

    template<flot E>
    _Mat3x3(std::initializer_list<E> list) noexcept {
        int i = 0;
        
        if(list.size() < 10){
            for(; i < list.size(); i++)
                values[i] = static_cast<T>(*(list.begin() + i));
        }

        for(; i < 9; i++)
            values[i] = 0;
    }

    _Mat3x3(const _Mat3x3<T>& mat) noexcept {
        for(int i = 0; i < 9; i++)
            values[i] = mat.values[i];
    }

    _Mat3x3<T>& operator=(const _Mat3x3<T>& mat) noexcept {
        for(int i = 0; i < 9; i++)
            values[i] = mat.values[i];
        return *this;
    }

    template<typename E>
    _Mat3x3<T>& operator*=(E scalar) noexcept {
        for(int i = 0; i < 9; i++)
           values[i] *= scalar;
        return *this;
    }

    template<typename E>
    _Mat3x3<T> operator*(E scalar) noexcept {
        return _Mat3x3<T>(*this) *= scalar;
    }

    _Mat3x3<T>& operator+=(const _Mat3x3& mat) noexcept {
        for(int i = 0; i < 9; i++)
           values[i] += mat.values[i];
        return *this;
    }

    _Mat3x3<T> operator+(const _Mat3x3<T>& mat) noexcept {
        return _Mat3x3<T>(*this) += mat;
    }

    _Mat3x3<T>& operator*=(const _Mat3x3& mat) noexcept {
        _Mat3x3<T> temp;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                T sum =0;
                for(int k = 0; k < 3; k++)
                    sum += values[i * 3 + k] * mat.values[k * 3 + j];
                temp.values[i * 3 + j] = sum;
            }
        }
        *this = temp;
        return *this;
    }

    _Mat3x3<T> operator*(const _Mat3x3<T>& mat) noexcept {
        return _Mat3x3<T>(*this) *= mat;
    }

    template<flot E>
    _Vec2<E> operator*(const _Vec2<E>& v) noexcept {
        _Vec2<E> temp;
        temp.SetX() = values[0] * v.GetX() + values[1] * v.GetY() + values[2] * 1;
        temp.SetY() = values[3] * v.GetX() + values[4] * v.GetY() + values[5] * 1;
        return temp;
    }

    T& operator()(int row, int column) noexcept{
        return values[row * 3 + column];
    }

    static _Mat3x3<T> Identity() noexcept {
        return _Mat3x3<T>{
            static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
        };
    }

    template<flot E>
    static _Mat3x3<E> Rotation(E angle) noexcept {
        E sine = std::sin(angle);
        E cosine = std::cos(angle);

        return _Mat3x3<E>{
            cosine, -sine, static_cast<E>(0),
            sine, cosine, static_cast<E>(0),
            static_cast<E>(0), static_cast<E>(0), static_cast<E>(1)
        };
    }

    template<typename E>
    static _Mat3x3<T> Scale(E scalar) noexcept {
        return _Mat3x3<T>{
            static_cast<T>(scalar), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(scalar), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(scalar)
        };
    }

    template<flot E>
    static _Mat3x3<T> Translation(const _Vec2<E>& v) noexcept {
        return _Mat3x3<T>{
            static_cast<T>(1), static_cast<T>(0), static_cast<T>(v.GetX()),
            static_cast<T>(0), static_cast<T>(1), static_cast<T>(v.GetY()),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
        };
    }

    friend std::ostream& operator<<(std::ostream& out, const _Mat3x3& mat){
        return out << mat.values[0] << " " << mat.values[1] << " " << mat.values[2] << "\n"
                   << mat.values[3] << " " << mat.values[4] << " " << mat.values[5] << "\n"
                   << mat.values[6] << " " << mat.values[7] << " " << mat.values[8] << std::endl;
    }

private:
    T values[9];
};
typedef _Mat3x3<float> Mat3x3;
#endif