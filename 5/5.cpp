#include <iostream>
#include <string>
#include <algorithm>

using std::cout, std::string, std::endl;

void move_spaces(string& s) {
    std::stable_sort(s.begin(), s.end(), [](const char& a, const char& b){return (b == ' ');});
}

int main() {
    string x = "cats and dogs";
    string y = " cats   and  dogs    ";
    move_spaces(x);
    move_spaces(y);
    cout << x << "<END>" << endl;
    cout << y << "<END>" << endl;
    return 0;
}
