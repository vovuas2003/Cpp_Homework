/*
    Напишите функцию:
    template <typename RandIt, typename Comparator>
    void parallelSort(int n, RandIt start, RandIt finish, Comparator comp)
    которая будет сортировать диапазон, задаваемый итераторами start и finish, используя компаратор comp.
    Алгоритм должен работать в n потоков.
    Например, следующий вызов программы:
    parallelSort(4, v.begin(), v.end(), [](int a, int b) {return a > b;});
    должен сортировать вектор целых чисел v по убыванию, используя 4 потока.
    При реализации этой функции можно использовать однопоточную версию функции std::sort.
    Протестируйте функцию, замерив скорость работы однопоточной и многопоточной версии.
*/


#include <functional>

#define DEBUG

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdint>
using std::cout, std::endl, std::size_t;
using namespace std::chrono_literals;

template <typename RandIt, typename Comparator>
bool issorted(RandIt first, RandIt last, Comparator comp) {
  if (first != last) {
    auto next = first;
    while (++next != last) {
      if (comp(*next, *first)) {
        return false;
      }
      first = next;
    }
  }
  return true;
}

template <typename RandIt, typename Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp) {
    if(n == 1) {
        std::sort(start, finish, comp);
    } else {
        /*
        https://stackoverflow.com/questions/19072808/using-stdpartition-with-quick-sort
        */
        if(start == finish) return; // >= ???
        using T = std::iter_value_t<RandIt>;
        T pivot = *start;
        RandIt middle = std::partition(start, finish, [pivot](const T& t){return comp(t, pivot)}); // [](RandIt::value_type t){}
        parallelSort(n / 2, start, middle);
        parallelSort(n - (n / 2), middle + 1, finish); // std::async with std::launch async
}

/*
https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F
template< typename BidirectionalIterator, typename Compare >
void quick_sort( BidirectionalIterator first, BidirectionalIterator last, Compare cmp ) {
   if( first != last ) {
     BidirectionalIterator left  = first;
     BidirectionalIterator right = last;
     BidirectionalIterator pivot = left++;
     while( left != right ) {
       if( cmp( *left, *pivot ) ) {
          ++left;
       } else {
          while( (left != --right) && cmp( *pivot, *right ) );
          std::iter_swap( left, right );
       }
     }
     --left;
     std::iter_swap( first, left );
     quick_sort( first, left, cmp );
     quick_sort( right, last, cmp );
   }
 }
*/

int main()
{
#ifdef DEBUG
    std::vector<double> numbers = {1.2, 5.1, 8.2, 1.0, 0.2, 5.0, 7.8, 7.7, 11.5, 2.3, 55.66, 17.8, 12.3, 9.7, 15.51, 4.2};
    std::vector<double> v = numbers;
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {return a > b;});
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Time to sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;
    bool check = issorted(numbers.begin(), numbers.end(), [](int a, int b) {return a > b;});
    if(!check) cout << "Wrong sort" << endl;
    else cout << "OK!" << endl;
    cout << endl;
    int hardware_threads = std::thread::hardware_concurrency();
    int n = (hardware_threads != 0 ? hardware_threads : 2);
    cout << "hardware: " << hardware_threads << "; n: " << n << endl;
    start = std::chrono::high_resolution_clock::now();
    parallelSort(n, v.begin(), v.end(), [](int a, int b) {return a > b;});
    end = std::chrono::high_resolution_clock::now();
    cout << "Time to parallel sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;
    check = issorted(v.begin(), v.end(), [](int a, int b) {return a > b;});
    if(!check) cout << "Wrong parallel sort" << endl;
    else cout << "OK!" << endl;
#else
    cout << "Generating numbers!" << endl;
    std::vector<uint64_t> numbers(2e8);
    numbers[0] = 123456789;
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }
    cout << "Numbers generated!" << endl << endl;
    std::vector<uint64_t> v = numbers;
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {return a > b;});
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Time to sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;
    bool check = issorted(numbers.begin(), numbers.end(), [](int a, int b) {return a > b;});
    if(!check) cout << "Wrong sort" << endl;
    else cout << "OK!" << endl;
    cout << endl;
    start = std::chrono::high_resolution_clock::now();
    parallelSort(4, v.begin(), v.end(), [](int a, int b) {return a > b;});
    end = std::chrono::high_resolution_clock::now();
    cout << "Time to parallel sort = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " milliseconds." << endl;
    check = issorted(v.begin(), v.end(), [](int a, int b) {return a > b;});
    if(!check) cout << "Wrong parallel sort" << endl;
    else cout << "OK!" << endl;
#endif
    return 0;
}
