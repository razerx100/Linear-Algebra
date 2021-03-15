#include <iostream>
#include "Vector.hpp"

int main() {
    Vec2 v = {2.5f, 6.6f};
    Vec2 v2 = v;
    std::cout << (v2 / 2.0f) << v2.Magnitude();
    return 0;
}