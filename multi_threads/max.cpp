/*
    Задача:

        В данном примере написана функция getMax, которая находит максимум из чисел в векторе.
        При этом вычисления проходят однопоточно.


        Вам нужно написать функцию     

            uint64_t getMaxPar(int n, const std::vector<uint64_t>& v)

        которая будет делать то же самое, но только использовать для этого n потоков.
*/




#include <functional>

//#define DEBUG

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>
using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;

uint64_t getMax(const std::vector<uint64_t>& v)
{
    uint64_t result = v.at(0);
    for (auto el : v)
    {
        if (el > result)
            result = el;
    }
    return result;
}

void getMaxOne(std::vector<uint64_t>::const_iterator first, std::vector<uint64_t>::const_iterator last, uint64_t& result)
{
    result = *first;
    for(++first; first != last; ++first)
    {
        if(*first > result)
        {
            result = *first;
        }
    }
}

uint64_t getMaxPar(int n, const std::vector<uint64_t>& v)
{
    unsigned long const length = v.size();
    unsigned long block_size = length;
    if(n == 0)
    {
        unsigned long const hardware_threads = std::thread::hardware_concurrency();
        n = (hardware_threads != 0 ? hardware_threads : 2);
#ifdef DEBUG
        cout << "n == 0 => n = " << n << endl;
#endif
    }
    block_size /= n;
    std::vector<uint64_t> results(n);
    std::vector<std::thread> threads(n - 1);
    std::vector<uint64_t>::const_iterator block_start = v.begin();
    for(unsigned long i = 0; i < (n - 1); ++i)
    {
        std::vector<uint64_t>::const_iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(getMaxOne, block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    getMaxOne(block_start, v.end(), results[n - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return getMax(results);
}

int main()
{
    cout << "Generating numbers!" << endl;
    //std::vector<uint64_t> numbers(5e8);
    std::vector<uint64_t> numbers(2e8);
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl << endl;

    auto start = std::chrono::high_resolution_clock::now();
    uint64_t m = getMax(numbers);
    cout << "Maximum = " << m << endl;
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Time to calclulate max = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl << endl;

    start = std::chrono::high_resolution_clock::now();
    m = getMaxPar(20, numbers);
    cout << "Maximum = " << m << endl;
    end = std::chrono::high_resolution_clock::now();
    cout << "Time to calclulate max = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;

    return 0;
}
