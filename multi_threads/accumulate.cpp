//#define DEBUG

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <cstdint>
using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first,last);
    if(!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
#ifdef DEBUG
    cout << "Amount of active threads: " << num_threads << ", max hardware: " << hardware_threads << endl;
#endif
    unsigned long const block_size = length / num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    Iterator block_start = first;
    for(unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    cout << "Generating numbers!" << endl;
    std::vector<uint64_t> numbers(5e8);
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl;




    auto start = std::chrono::high_resolution_clock::now();


    uint64_t m = parallel_accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum = " << m << endl;


    auto end = std::chrono::high_resolution_clock::now();
    cout << "Time to calclulate sum = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;

    start = std::chrono::high_resolution_clock::now();


    m = std::accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum = " << m << endl;


    end = std::chrono::high_resolution_clock::now();
    cout << "Time to calclulate sum = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;
}
