#include <iostream>

struct Book {
    char title[100];
    int pages;
    float price;
};

bool isExpensive(const Book& a) {
    bool f = false;
    if (a.price > 1000) {
        f = true;
    }
    return f;
}

int main() {
    Book a = {"TECT2", 555, 999.99};
    Book b = {"TECT2", 777, 1299.99};
    std::cout << std::boolalpha << isExpensive(a) << std::endl << std::boolalpha << isExpensive(b);
    return 0;
}
