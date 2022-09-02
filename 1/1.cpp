#include <iostream>

namespace myspace {
    void print_n_times(char str[], int n = 10) {
        for(int i = 0; i < n; i++) {
            std::cout << str;
        }
        std::cout << std::endl;
    }
}

int main() {
    myspace::print_n_times("Hello! ");
    myspace::print_n_times("World ", 5);
    return 0;
}
