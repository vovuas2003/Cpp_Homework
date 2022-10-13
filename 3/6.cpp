#include <iostream>

int main() {
    int* a = new int{123};
    std::cout << *a << std::endl;
    delete a;
    std::string* b = new std::string{"Cats and Dogs"};
    std::cout << *b << std::endl;
    delete b;
    int* c = new int[5]{10, 20, 30, 40, 50};
    for(int i = 0; i < 5; i++) {
        std::cout << c[i] << ' ';
    }
    std::cout << std::endl;
    delete[] c;
    std::string* d = new std::string[3]{"Cat", "Dog", "Mouse"};
    for(int i = 0; i < 3; i++) {
        std::cout << d[i] << ' ';
    }
    std::cout << std::endl;
    std::string_view* e = new std::string_view[3]{d[0], d[1], d[2]};
    for(int i = 0; i < 3; i++) {
        std::cout << e[i] << ' ';
    }
    delete[] d;
    delete[] e;
    return 0;
}
