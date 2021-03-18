#include <iostream>
#include "Mat3x3.hpp"

int main() {
    Vec2 vec = {5, 7};
    Vec2 vR = vec;
    vR.Rotate(M_PI / 2);
    std::cout << "Vector rotation : " << vR;

    std::cout << "Matrix rotaiton : " << Mat3x3::Rotation(M_PI / 2) * vec;
    return 0;
}