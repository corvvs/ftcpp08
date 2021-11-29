#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
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
    return (time_now.tv_sec * 1000000) + (time_now.tv_usec);
}

void    pdf_test(void) {
    say("[ PDF test ]");
    Span sp = Span(5);
    sp.addNumber(5);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    tester("shortest is", sp.shortestSpan(), 2u);
    tester("longest is", sp.longestSpan(), 14u);
}

void    blank_span(void) {
    say("[ blank Span ]");
    try {
        std::cout
            << Constants::kTextWarning
            << "make a size 0 Span." << std::endl
            << Constants::kTextReset;
        Span sp(0);
        std::cout
            << Constants::kTextWarning
            << "made it!" << std::endl
            << Constants::kTextReset;
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}


void    duplication_test(void) {
    say("[ duplication ]");
    try {
        std::cout
            << Constants::kTextWarning
            << "make a size 2 Span, and add two 1." << std::endl
            << Constants::kTextReset;
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(1);
        tester("shortest of sp is", sp.shortestSpan(), 0u);
        tester("longest of sp is", sp.longestSpan(), 0u);
        std::cout
            << Constants::kTextWarning
            << "ok, and one more 1." << std::endl
            << Constants::kTextReset;
        sp.addNumber(1);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    std::cout
        << Constants::kTextWarning
        << "did you see an exception?" << std::endl
        << Constants::kTextReset;
}

void    self_assignation(void) {
    say("[ self assignation ]");
    try {
        Span sp(2);
        sp.addNumber(1);
        try {
            std::cout
                << Constants::kTextWarning
                << "construct a Span sp2 by copying another Span sp." << std::endl
                << "old and new Span's are independent." << std::endl
                << "add 2 into sp2 and get shortest span." << std::endl
                << "sp2 has only 1 number, so an exception will be caused." << std::endl
                << Constants::kTextReset;
            Span sp2(sp);
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
                << "now, assign Span sp into another Span sp3." << std::endl
                << "old and new Span's are independent." << std::endl
                << "add 2 into sp3 and get shortest span." << std::endl
                << "sp3 has only 1 number, so an exception will be caused." << std::endl
                << Constants::kTextReset;
            Span sp3(10000000);
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
        << "the distance is very large, so the algorithm doesn't work well." << std::endl
        << Constants::kTextReset;
    unsigned int N = 1000000;
    Span sp(N);
    for (unsigned i = 0; i <= N; i += 1) {
        try {
            int k = static_cast<double>(RAND_MAX) / N * i;
            // time_t ta = gettime();
            sp.addNumber(k);
            // time_t tb = gettime();
            // std::cerr << (tb - ta) << std::endl;
            if (i % (N / 20) == 0) {
                unsigned int shortest = sp.shortestSpan();
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
    tester("numbers the span has", sp.getAdded(), N);
    tester("should be equal to N", sp.getN(), sp.getAdded());
    std::cout << sp.shortestSpan() << " " << sp.longestSpan() << std::endl;
}

void    random_large_test(void) {
    say("[ large random ]");
    std::cout
        << Constants::kTextWarning
        << "adding many random numbers." << std::endl
        << Constants::kTextReset;
    std::srand((unsigned int) std::time(NULL));
    unsigned int N = 10000000;
    Span sp(N);
    std::cout << "RAND_MAX: " << RAND_MAX << std::endl;
    for (unsigned i = 0; i <= N; i += 1) {
        try {
            // int k = static_cast<double>(rand()) * (1 - 2 * (rand() % 2));
            int k = static_cast<double>(rand() - rand()) / RAND_MAX * (INT_MAX / 10);
            // time_t ta = gettime();
            sp.addNumber(k);
            // time_t tb = gettime();
            // std::cerr << (tb - ta) << std::endl;
            if (i % (N / 20) == 0) {
                unsigned int shortest = sp.shortestSpan();
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
    tester("numbers the span has", sp.getAdded(), N);
    tester("should be equal to N", sp.getN(), sp.getAdded());
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
    Span                sp(N);
    // std::list<int>    vec;
    std::vector<int>    vec;
    for (int i = 0; i < N; i += 1) { 
        vec.push_back(i * 100);
    }
    // sp.addNumbers(vec.begin(), vec.end());
    sp.addNumbers(vec);
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
    Span sp(4);
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
    pdf_test();
    blank_span();
    duplication_test();
    self_assignation();
    random_large_test();
    uniform_large_test();
    iterator_test();
    widespread_test();
}
