#include <iostream>
#include <string>

template <typename T>
class Manager {
private:
    T* mPtr;
public:
    Manager() {
        mPtr = nullptr;
    }
    void allocate() {
        mPtr = (T*)malloc(sizeof(T));
    }
    void construct(const T& t) {
        new(mPtr) T{t};
    }
    T& get() {
        return *mPtr;
    }
    void destruct() {
        mPtr->~T();
    }
    void deallocate() {
        free(mPtr);
    }
};

int main() {
    Manager<std::string> a;
    a.allocate();

    a.construct("Cats and dogs");
    a.get() += " and elephant";
    std::cout << a.get() << std::endl;
    a.destruct();

    a.construct("Sapere aude");
    std::cout << a.get() << std::endl;

    a.destruct();
    a.deallocate();

    return 0;
}
