#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::endl, std::string, std::vector;

void string_vector_reverse(vector<string>& sv) {
    std::for_each(sv.begin(), sv.end(), [](string& s){std::reverse(s.begin(), s.end());});
    std::reverse(sv.begin(), sv.end());
}

int main() {
    vector<string> x {"cat", "dog", "mouse", "elephant"};
    vector<string> y {"a", "bc"};
    string_vector_reverse(x);
    string_vector_reverse(y);
    for (int i = 0, n = x.size(); i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    for (int i = 0, n = y.size(); i < n; i++) {
        cout << y[i] << " ";
    }
    return 0;
}
