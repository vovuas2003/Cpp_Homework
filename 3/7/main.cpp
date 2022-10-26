#include <iostream>
#include "miptstring.hpp"

using std::cout, std::endl;

int main() {
    mipt::String a{"Cat"};
    cout << a << endl;

    mipt::String* b = new mipt::String{"Dog"};
    cout << *b << endl;
    delete b;

    char *x = (char*)malloc(sizeof(mipt::String));
    mipt::String* c = new(x) mipt::String{"Elephant"};
    cout << *c << endl;
    c->~String();
    free(c);

    return 0;
}
