#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <fstream>
#include <algorithm>

//#define DEBUG

template<typename T>
class threadsafe_queue
{
private:
    std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }
};

threadsafe_queue<std::string> tsq;

void read() {
#ifdef DEBUG
    std::ifstream fin("invisible_man_1.txt");
#else
    std::ifstream fin("invisible_man.txt");
#endif
    std::string s;
    while(getline(fin, s)) {
        tsq.push(s);
    }
    tsq.push("__THE_END__");
}

void write() {
    std::string s;
    while(true) {
        tsq.wait_and_pop(s);
        if(s == "__THE_END__") {
            break;
        }
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        std::cout << s << std::endl;
    }
}

int main() {
    std::thread t1(read);
    std::thread t2(write);
    t1.join();
    t2.join();
    return 0;
}
