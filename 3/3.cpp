#include <iostream>
#include <string>

std::string operator*(std::string a, int n) {
    std::string otv = "";
    for(int i = 0; i < n; i++) {
        otv += a;
    }
    return otv;
}

int main() {
    std::string a = "PT!";
    std::cout << a * 5 << std::endl;
    return 0;
}
