#include <iostream>
#include <string_view>
#include <string>

std::string repeat1(std::string_view s) {
    std::string a = std::string(s);
    return a + a;
}

void repeat2(std::string& s) {
    s += s;
}

void repeat3(std::string* ps) {
    *ps += *ps;
}

std::string* repeat4(std::string_view s) {
    std::string* a = new std::string{repeat1(s)};
    return a;
}

int main() {
    std::string a = "PT!";
    a = repeat1(a);
    std::cout << a << std::endl;
    repeat2(a);
    std::cout << a << std::endl;
    repeat3(&a);
    std::cout << a << std::endl;
    std::string* b = repeat4(a);
    std::cout << *b << std::endl;
    delete(b);
    return 0;
}
