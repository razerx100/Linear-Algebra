#include <iostream>
#include "Vector.hpp"

int main() {
    Vec2 v = {2.5f, 6.6f};
    Vec2 v2 = v;
    std::cout << "Co-ordinates : " << v2;
    v2.Rotate(M_PI);
    std::cout << "Co-ordinates after rotation : " << v2;
    return 0;
}