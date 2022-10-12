#include <iostream>

std::string change(std::string s) {
    std::string otv = s;
    if (isupper(otv[0])) {
        otv[0] = tolower(otv[0]);
    } else {
        otv[0] = toupper(otv[0]);
    }
    return otv;
}

int main() {
    std::string a = "Cat";
    a = change(a);
    std::cout << a << std::endl;
    std::string b = "dog";
    b = change(b);
    std::cout << b << std::endl;
    return 0;
}
