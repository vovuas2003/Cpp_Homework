#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::string, std::pair, std::cout, std::endl, std::vector;

template <typename T>
T mymax(const vector<T>& v) {
    T max = T();
    for(int i = 0, size = v.size(); i < size; i++) {
        if (v[i] > max)
                max = v[i];
    }
    return max;
}

int main() {
    vector<int> a {147, 54, 166, 69, 43, 44, 106, 91, 28, 64};
    cout << mymax(a) << endl;
    vector<float> b {103.15, 60.56, 25.37, 24.9, 21.51, 132.39, 126.6, 194.11, 91.42, 156.05};
    cout << mymax(b) << endl;
    vector<string> c {"iital", "xurawdjr", "poediepb", "mjjplhsb", "vxtruwjprq", "ctrhtnbr"};
    cout << mymax(c) << endl;
    vector<pair<int, int>> d {{147, 54}, {166, 69}, {43, 44}, {106, 91}, {28, 64}};
    pair<int, int> e = mymax(d);
    cout << "{" << e.first << ", " << e.second << "}";
    return 0;
}
