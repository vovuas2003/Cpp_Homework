#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>
#include <cctype>

using std::cout, std::endl, std::string, std::string_view, std::boolalpha;

bool isIdentifier(string_view s) {
    if (!(isalpha(s[0]) || s[0] == '_')) {
        return false;
    }
    if (std::all_of(s.begin(), s.end(), [](char c){return isalpha(c) || isdigit(c) || c == '_' ;})) {
        return true;
    }
    return false;
}

int main() {
    string a = "a";
    string b = "isIdentifier";
    string c = "_name123";
    string d = "hello world";
    string e = "123name";
    string f = "my-name";
    cout << boolalpha << isIdentifier(a) << endl;
    cout << boolalpha << isIdentifier(b) << endl;
    cout << boolalpha << isIdentifier(c) << endl;
    cout << boolalpha << isIdentifier(d) << endl;
    cout << boolalpha << isIdentifier(e) << endl;
    cout << boolalpha << isIdentifier(f) << endl;
    return 0;
}
