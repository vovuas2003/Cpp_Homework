#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using std::cout, std::endl, std::string, std::boolalpha;

bool my_upper(const string& s) {
    int f = std::count_if(s.begin(), s.end(), [](char c){return (islower(c) && isalpha(c));});
    if(f) {
        return false;
    }
    return true;
}

int main() {
    string a = "Cats and Dogs!";
    string b = "CATS AND DOGS!";
    string c = "ABc123!#?";
    string d = "ABC123!#?";
    cout << boolalpha << my_upper(a) << endl;
    cout << boolalpha << my_upper(b) << endl;
    cout << boolalpha << my_upper(c) << endl;
    cout << boolalpha << my_upper(d) << endl;
    return 0;
}
