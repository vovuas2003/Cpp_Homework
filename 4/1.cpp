#include <vector>
#include <iostream>

int sumEven(const std::vector<int>& v) {
    int s = 0;
    for(int i = 0; i < v.size(); i++) {
        if(v[i] % 2 == 0) {
            s += v[i];
        }
    }
    return s;
}

int main() {
    std::vector<int> x{4, 8, 15, 16, 23, 42};
    std::cout << sumEven(x);
    return 0;
}
