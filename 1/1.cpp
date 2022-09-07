#include <iostream>

namespace myspace {
    void printNTimes(const char* str, int n = 10) {
        for(int i = 0; i < n; i++) {
            std::cout << str;
        }
        std::cout << std::endl;
    }
}

int main() {
    myspace::printNTimes("Hello! ");
    myspace::printNTimes("World ", 5);
    return 0;
}
