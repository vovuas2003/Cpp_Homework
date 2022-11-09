#include <iostream>
#include "4.hpp"
#include <string_view>
#include <string>
#include <vector>

using std::cout, std::endl, std::string, std::string_view, std::vector;

int main() {
    string a = "18:05:35";
    string_view av = a;
    string b = "22:10:45";
    string_view bv = b;

    Time x = av;
    Time y = bv;
    cout << x + y << endl << endl;

    string c = "12:20:05 05:45:30 22:10:45";
    string_view cv = c;
    vector<Time> z = getTimesFromString(cv);
    for (int i = 0, size = z.size(); i < size; i++) {
	cout << z[i] << endl;
    }
    cout << endl << sumTimes(z) << endl;

    return 0;
}
