#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "number.h"

Number fib(int n) {
    Number a = 0;
    Number b = 1;
    for (int i = 1; i <= n; ++i) {
	if (i % 2) {
	    a += b;
	} else {
	    b += a;
	}
    }
    if (n % 2) {
	return b;
    }
    return a;
}

Number f(int n) {
    Number result {1};
    for (int i = 2; i < n + 1; ++i) {
	result = Number(i) * result;
    }
    return result;
}

void grad(Number n)
{
    std::cout << "n = " << n;
    Number max = n;
    unsigned long long int steps = 0;
    while (n != Number(1)) {
	if (n > max) {
	    max = n;
	}
	if (n.isEven()) {
	    n.div2();
	} else {
	    n = Number(3) * n + Number(1);
	}
	steps += 1;
    }
    std::cout << " steps = " << steps << " max = " << max << std::endl;
}

int main() {
        std::cout << "F(1000) = " << fib(1000) << std::endl; 
        std::cout << "1000! = " << f(1000) << std::endl;
        grad(Number("7"));
        grad(Number("256"));
        grad(Number("1117065"));
        grad(Number("4761963248413673697"));
        grad(Number("90560792656972947582439785608972465789628974587264056284658721771"));
	return 0;
}