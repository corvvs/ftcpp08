#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>
#include "span.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << std::endl << str << std::endl << std::endl;
}

time_t gettime(void) {
    struct timeval time_now;
    gettimeofday(&time_now, nullptr);
    return (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

void    self_assignation(void) {
    say("[ self assignation ]");
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

void    overflow_test(void) {
    say("[ overflow ]");
    span sp(4);
    sp.addNumber(INT_MAX);
    sp.addNumber(INT_MIN + 1);
    std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
    sp.addNumber(INT_MIN);
    std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
    sp.addNumber(INT_MIN);
    std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
}

void    random_large_test(void) {
    say("[ large random ]");
    std::srand((unsigned int) std::time(NULL));
    unsigned int N = 100000;
    span sp(N);
    std::cout << "RAND_MAX: " << RAND_MAX << std::endl;
    for (unsigned i = 0; i <= N; i += 1) {
        try {
            // int k = static_cast<double>(rand()) * (1 - 2 * (rand() % 2));
            int k = static_cast<double>(rand() - rand()) / RAND_MAX * (INT_MAX / 10);
            sp.addNumber(k);
            unsigned int shortest = sp.shortestSpan();
            if (i % (N / 20) == 0) {
                unsigned int longest = sp.longestSpan();
                std::cout << i << " " << shortest << " " << longest << std::endl;
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
    overflow_test();
    random_large_test();
}
