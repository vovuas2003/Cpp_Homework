#include <vector>
#include <span>
#include <iostream>

void myprint(std::vector<int>);

std::vector<int> lastDigits1(const std::vector<int>& v) {
    std::vector<int> s;
    s.resize(v.size());
    for(int i = 0; i < v.size(); i++) {
        s[i] = v[i] % 10;
    }
    return s;
}

void lastDigits2(std::vector<int>& v) {
    for(int i = 0; i < v.size(); i++) {
        v[i] = v[i] % 10;
    }
}

void lastDigits3(std::vector<int>* pv) {
    for(int i = 0; i < pv->size(); i++) {
        (*pv)[i] = (*pv)[i] % 10;
    }
}

void lastDigits4(std::span<int> sp) {
    for(int i = 0; i < sp.size(); i++) {
        sp[i] = sp[i] % 10;
    }
}

int main() {
    std::vector<int> a{41, 83, 153, 479847};
    std::vector<int> b = lastDigits1(a);
    myprint(b);
    lastDigits2(a);
    myprint(a);
    std::vector<int> c{41, 83, 153, 479847};
    lastDigits3(&c);
    myprint(c);
    std::vector<int> d{41, 83, 153, 479847};
    lastDigits4(d);
    myprint(d);
    return 0;
}

void myprint(std::vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
