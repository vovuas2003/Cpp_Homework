#include <iostream>
#include <string>

void truncateToDot(std::string& s) {
    s.resize(s.find('.'));
}

int main() {
    std::string a = "cat.dog.mouse.elephant.tiger.lion";
    std::string b = "wikipedia.org";
    std::string c = ".com";
    truncateToDot(a);
    truncateToDot(b);
    truncateToDot(c);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    return 0;
}
