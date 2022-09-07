#include <iostream>

int cubeV(int a) {
    return a * a * a;
}

void cubeR(int& a) {
    a = a * a * a;
}

int main() {
    int x = 2;
    std::cout << x << std::endl;
    cubeR(x);
    std::cout << x << std::endl;
    std::cout << std::endl;
    x = 2;
    std::cout << x << std::endl;
    x = cubeV(x);
    std::cout << x << std::endl;
}
