#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl, std::string, std::vector;

template <typename T>
class Ref {
private:
    T* mPtr;
public:
    Ref(T& t) {
        mPtr = &t;
    }
    Ref(Ref& t) {
        mPtr = t.mPtr;
    }
    Ref() {
        mPtr = nullptr;
    }
    T& get() {
        return *mPtr;
    }
    T operator=(const T& t) {
        new(mPtr) T{t};
        return *mPtr;
    }
    T operator+(const T& t) {
        return *mPtr + t;
    } 
    T operator+=(const T& t) {
        *mPtr = *mPtr + t;
        return *mPtr;
    }
    T* operator->() {
        return mPtr;
    }
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, Ref<U> r);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Ref<T> r) {
    out << *(r.mPtr);
    return out;
}

void toUpper(Ref<string> r) {
    for(size_t i = 0; i < r->size(); ++i) {
        r.get()[i] = toupper(r.get()[i]);
    }
}

int main() {
    int a = 10;
    Ref<int> ra = a;
    ra += 10;
    cout << a << " " << ra << endl;

    string s = "Cat";
    Ref<string> rs = s;
    rs = "Mouse";
    rs += "Elephant";
    cout << rs << endl;
    cout << s << endl;

    toUpper(s);
    cout << s << endl;

    vector<string> animals {"Cat", "Dog", "Elephant", "Worm"};
    vector<Ref<string>> refs {animals.begin(), animals.end()};

    for(int i = 0; i < refs.size(); ++i) {
        refs[i] += "s";
    }
    
    for(int i = 0; i < refs.size(); ++i) {
        cout << animals[i] << " ";
    }
    cout << endl;

    return 0;
}
