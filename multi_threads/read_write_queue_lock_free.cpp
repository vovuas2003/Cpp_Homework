/*
    ONLY ONE THREAD CAN POP
    ONLY ONE THREAD CAN PUSH
*/

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
class lock_free_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node* next;
        node():
            next(nullptr)
        {}
    };
    std::atomic<node*> head;
    std::atomic<node*> tail;
    node* pop_head()
    {
        node* const old_head=head.load();
        if(old_head==tail.load())
        {
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }
public:
    lock_free_queue():
        head(new node),tail(head.load())
    {}
    lock_free_queue(const lock_free_queue& other)=delete;
    lock_free_queue& operator=(const lock_free_queue& other)=delete;
    ~lock_free_queue()
    {
        while(node* const old_head=head.load())
        {
            head.store(old_head->next);
            delete old_head;
        }
    }
    std::shared_ptr<T> pop()
    {
        node* old_head=pop_head();
        if(!old_head)
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(old_head->data);
        delete old_head;
        return res;
    }
void push(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
        node* p=new node;
        node* const old_tail=tail.load();
        old_tail->data.swap(new_data);
        old_tail->next=p;
        tail.store(p);
    }
};

lock_free_queue<std::string> tsq;

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
