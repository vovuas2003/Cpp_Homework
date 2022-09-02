#include <iostream>

void cube(int& a) {
    a = a * a * a;
}

int main() {
    int x = 2;
    std::cout << x << std::endl;
    cube(x);
    std::cout << x << std::endl;
}
