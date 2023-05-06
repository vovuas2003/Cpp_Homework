#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std::chrono_literals;

std::string s = "";
std::mutex m;

void read() {
    std::ifstream fin("invisible_man_1.txt");
    bool flag = true;
    while(flag) {
        while(true) {
            m.lock();
            if(s == "") {
                if(!getline(fin, s)) {
                    flag = false;
                    s = "THE_END";
                }
                m.unlock();
                break;
            } else {
                m.unlock();
                std::this_thread::sleep_for(1ms);
            }
        }
    }
}

void write() {
    bool flag = true;
    while(flag) {
        while(1) {
            m.lock();
            if (s == "") {
                m.unlock();
                std::this_thread::sleep_for(1ms);
            } else {
                if(s == "THE_END") {
                    flag = false;
                    m.unlock();
                    break;
                }
                std::transform(s.begin(), s.end(), s.begin(), ::toupper);
                std::cout << s << std::endl;
                s = "";
                m.unlock();
            }
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
