#include <iostream>
#include <cstdlib>
#include "easyfind.hpp"
#include <vector>
#include <list>
#include <set>
#include <deque>
#include "Constants.hpp"
#include "easyfind.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
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

template<class T>
void    print_container(T& c) {
    typename T::iterator it = c.begin();
    typename T::iterator et = c.end();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != c.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "]" << std::endl;
}

template < class Container >
void find_test(
    Container& c,
    int should_found,
    int should_not_found
) {
    typename Container::iterator result_it = easyfind(c, should_found);
    say("find 313 from container.");
    tester("found something",       result_it != c.end(),   true);
    tester("found value is 314",    *result_it,             should_found);
    say("find 1 from container.");
    result_it = easyfind(c, should_not_found);
    tester("not found 1",           result_it == c.end(),   true);
}

int main() {
    const int args[] = {
        -10, 100, 314, -15926535
    };

    int should_found = 314;
    int should_not_found = 1;
    int n = 4;
    try {
        say("[ vector ]");
        typedef std::vector<int> Container;
        Container arr(n);
        for(int i = 0; i < n; i += 1) {
            arr[i] = args[i];
        }
        std::cout << "container is: ";
        print_container(arr);
        say("(variable test)");
        find_test(arr, should_found, should_not_found);
        Container& carr = arr;
        say("(const test)");
        find_test(carr, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ list ]");
        typedef std::list<int> Container;
        Container arr(n);
        for(int i = 0; i < n; i += 1) {
            arr.push_back(args[i]);
        }
        std::cout << "container is: ";
        print_container(arr);
        std::cout << "container is: ";
        print_container(arr);
        say("(variable test)");
        find_test(arr, should_found, should_not_found);
        Container& carr = arr;
        say("(const test)");
        find_test(carr, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ set ]");
        typedef std::set<int> Container;
        Container arr;
        for(int i = 0; i < n; i += 1) {
            arr.insert(args[i]);
        }
        std::cout << "container is: ";
        print_container(arr);
        say("(variable test)");
        find_test(arr, should_found, should_not_found);
        Container& carr = arr;
        say("(const test)");
        find_test(carr, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ deque ]");
        typedef std::deque<int> Container;
        Container arr;
        for(int i = 0; i < n; i += 1) {
            arr.push_back(args[i]);
        }
        std::cout << "container is: ";
        print_container(arr);
        say("(variable test)");
        find_test(arr, should_found, should_not_found);
        Container& carr = arr;
        say("(const test)");
        find_test(carr, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    return 0;
}
