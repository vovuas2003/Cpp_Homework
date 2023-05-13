#include <iostream>
#include <mutex>
#include <string>
#include <future>
#include <algorithm>
#include <functional>
#include "image.hpp"

//#define DEBUG

std::mutex m;

void work(std::string s) {
    Image im;
    if(!im.loadPPM("ppm_images/" + s)) {
        {
            std::lock_guard<std::mutex> lk(m);
            std::cout << "File " << s << " doesn't exist!" << std::endl;
        }
        return;
    }
    double r = 0, g = 0, b = 0;
    int w = im.getWidth();
    int h = im.getHeight();
    int n = w * h;
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            auto pixel = im.getPixel(i, j);
            r += pixel.r;
            g += pixel.g;
            b += pixel.b;
        }
    }
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << "Average color of " << s << " is: (" << r/n << ", " << g/n << ", " << b/n << ")" << std::endl;
    }
}

void read() {
    std::string s;
    std::vector<std::future<void>> f;
    while(true) {
        {
            std::lock_guard<std::mutex> lk(m);
            std::cout << "Enter image name: ";
            getline(std::cin, s);
        }
        if(s == "") continue;
        if(s == "quit") break;
        f.push_back(std::async(std::launch::async, work, s));
    }
    std::for_each(f.begin(), f.end(), std::mem_fn(&std::future<void>::get));
}

int main() {
    read();
    return 0;
}
