#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <fstream>

std::string s = "";
std::mutex m;

void read() {
    ifstream fin;
    fin.open("invisible_man.txt");
    bool flag = true;
    while(flag) {
        while(true) {
            m.lock();
            if(s == "") {
                getline(fin, s);
                // if(EOF) flag = false
                m.unlock();
                break;
            } else {
                m.unlock();
                // sleep
            }
        }
    }
    // сообщить через глобальный флаг, защищённый другим мьютексом, функции write, что EOF
    fin.close();
}

void write() {
    while(1) {
        while(1) {
            m.lock();
            if (s == "") {
                m.unlock();
            } else {
                // s.toupper, cout << s
                m.unlock();
            }
    }
}

int main() {
    std::thread t1(read);
    std::thread t2(write);
    t1.join();
    t2.join();
    return 0;
}
