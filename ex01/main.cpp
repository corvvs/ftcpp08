#include <iostream>
#include <algorithm>
#include <vector>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>
#include "span.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << std::endl << str << std::endl << std::endl;
}

template <typename Result>
void    tester(
    const std::string& title,
    const Result& result,
    const Result& expected,
    const bool ignorable = false
) {
    bool ok = result == expected;
    const std::string color =
        ok
            ? Constants::kTextInfo
            : ignorable
                ? Constants::kTextWarning
                : Constants::kTextError;
    std::cout
        << color
        << ((result == expected) ? "[ok] " : "[KO] ")
        << title
        << ": "
        << std::boolalpha << result;
    if (!ok) {
        std::cout
            << "(expected: " << expected << ")";
    }
    std::cout
        << Constants::kTextReset << std::endl;
    if (!ok && !ignorable) {
        throw std::string("** detected KO test **");
    }
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
            std::cout
                << Constants::kTextWarning
                << "construct a span sp2 by copying another span sp." << std::endl
                << "old and new span's are independent." << std::endl
                << "add 2 into sp2 and get shortest span." << std::endl
                << "sp2 has only 1 number, so an exception will be caused." << std::endl
                << Constants::kTextReset;
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
        try {
            std::cout
                << Constants::kTextWarning
                << "now, assign span sp into another span sp3." << std::endl
                << "old and new span's are independent." << std::endl
                << "add 2 into sp3 and get shortest span." << std::endl
                << "sp3 has only 1 number, so an exception will be caused." << std::endl
                << Constants::kTextReset;
            span sp3(10000000);
            sp3 = sp;
            std::cout << sp3.shortestSpan() << " " << sp3.longestSpan() << std::endl;
            sp3.addNumber(3);
        } catch(std::exception& e) {
            std::cout
                << Constants::kTextError
                << e.what()
                << Constants::kTextReset << std::endl;
        }
        std::cout
            << Constants::kTextWarning
            << "sp still has only 1 number." << std::endl
            << "so, sp can accept one more number." << std::endl
            << Constants::kTextReset;
        sp.addNumber(3);
        tester("shortest of sp is", sp.shortestSpan(), 2u);
        tester("longest of sp is", sp.longestSpan(), 2u);
        std::cout
            << Constants::kTextWarning
            << "and now, sp is full." << std::endl
            << Constants::kTextReset;
        sp.addNumber(4);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}

void    uniform_large_test(void) {
    say("[ large uniform ]");
    std::cout
        << Constants::kTextWarning
        << "adding arithmetic sequence." << std::endl
        << "their distance is very large, so the algorithm doesn't work well." << std::endl
        << Constants::kTextReset;
    unsigned int N = 10000;
    span sp(N);
    for (unsigned i = 0; i <= N; i += 1) {
        try {
            int k = static_cast<double>(RAND_MAX) / N * i;
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

void    random_large_test(void) {
    say("[ large random ]");
    std::cout
        << Constants::kTextWarning
        << "adding many random numbers." << std::endl
        << Constants::kTextReset;
    // std::srand((unsigned int) std::time(NULL));
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
                std::cout << i << " shortest: " << shortest << " longest: " << longest << std::endl;
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

void    iterator_test() {
    say("[ add numbers by range iterator ]");
    std::cout
        << Constants::kTextWarning
        << "adding 1000 numbers: 0, 100, 200, ... , 99900" << std::endl
        << "finally, shortest span is 100 - 0 = 100," << std::endl
        << "and longest span is 99900 - 0 = 99900." << std::endl
        << Constants::kTextReset;
    int N = 1000;
    span                sp(N);
    std::vector<int>    vec;
    for (int i = 0; i < N; i += 1) { 
        vec.push_back(i * 100);
    }
    sp.addNumbers(vec.begin(), vec.end());
    tester("shortest is", sp.shortestSpan(), 100u);
    tester("longest is", sp.longestSpan(), 99900u);
}

void    widespread_test() {
    say("[ widespread test ]");
    std::cout
        << Constants::kTextWarning
        << "add INT_MAX and INT_MIN." << std::endl
        << "both shortest and longest span are INT_MAX - INT_MIN = UINT_MAX." << std::endl
        << Constants::kTextReset;
    span sp(4);
    sp.addNumber(INT_MAX);
    sp.addNumber(INT_MIN);
    tester("shortest is", sp.shortestSpan(), UINT_MAX);
    tester("longest is", sp.longestSpan(), UINT_MAX);
    std::cout
        << Constants::kTextWarning
        << "add a more INT_MAX and INT_MIN." << std::endl
        << "longest span should stay at UINT_MAX, but shortest shoule be 0." << std::endl
        << Constants::kTextReset;
    sp.addNumber(INT_MAX);
    sp.addNumber(INT_MIN);
    tester("shortest is", sp.shortestSpan(), 0u);
    tester("longest is", sp.longestSpan(), UINT_MAX);
}

int main() {
    self_assignation();
    random_large_test();
    uniform_large_test();
    iterator_test();
    widespread_test();
}
