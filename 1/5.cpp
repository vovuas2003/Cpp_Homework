#include <iostream>

struct Book {
    char title[100];
    int pages;
    float price;
};

void addPrice(Book& a, float x) {
    a.price += x;
}

int main() {
    Book b = {"TECT", 777, 1299.99};
    addPrice(b, 123.45);
    std::cout << b.price;
    return 0;
}
