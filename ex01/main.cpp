#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>
#include "span.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

time_t gettime(void) {
    struct timeval time_now;
    gettimeofday(&time_now, nullptr);
    return (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

void    self_assignation(void) {
    try {
        span sp(2);
        sp.addNumber(1);
        try {
            span sp2(sp);
            sp2.addNumber(2);
            std::cout << sp2.shortestSpan() << " " << sp2.longestSpan() << std::endl;
            sp2.addNumber(3);
        } catch(std::exception& e) {
            std::cout
                << Constants::kTextError
                << e.what()
                << Constants::kTextReset << std::endl;
        }
        sp.addNumber(3);
        std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
        sp.addNumber(4);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}

void    random_large_test(void) {
    std::srand((unsigned int) std::time(NULL));
    unsigned int N = 10;
    span sp(N);
    for (unsigned i = 0; i <= N; i += 1) {
        try {
            int k = rand();
            sp.addNumber(k);
            if (i % 1000 == 0) {
                std::cout << i << " " << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
            }
        } catch(std::exception& e) {
            std::cout
                << Constants::kTextError
                << e.what()
                << Constants::kTextReset << std::endl;
        }
    }
    std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
}

int main() {
    // time_t t0 = gettime();
    // std::cout << arr[0] << " " << t3 - t2 << std::endl;
    // time_t t1 = gettime();
    self_assignation();
    random_large_test();
}
