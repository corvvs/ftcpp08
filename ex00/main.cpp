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

template<class T>
void    print_container(const T& c) {
    typename T::const_iterator it = c.begin();
    typename T::const_iterator et = c.end();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != c.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "]" << std::endl;
}

template<class T>
void    print_container_over_iterator(T& c, typename T::iterator it) {
    typename T::iterator be = it;
    typename T::iterator et = c.end();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != be) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "]" << std::endl;
}

template<class T>
void    print_container_over_riterator(T& c, typename T::reverse_iterator it) {
    typename T::reverse_iterator be = it;
    typename T::reverse_iterator et = c.rend();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != be) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "]" << std::endl;
}

template<class T>
void    print_container_over_iterator(const T& c, typename T::const_iterator it) {
    typename T::const_iterator be = it;
    typename T::const_iterator et = c.end();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != be) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "]" << std::endl;
}

template<class T>
void    print_container_over_riterator(const T& c, typename T::const_reverse_iterator it) {
    typename T::const_reverse_iterator be = it;
    typename T::const_reverse_iterator et = c.rend();
    std::cout << "[";
    for(; it != et; ++it) {
        if (it != be) {
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
    say("(variable test)");
    {
        std::cout << "a given container is: ";
        print_container(c);
        typename Container::iterator result_it = easyfind(c, should_found);
        say("find 313 from the container.");
        tester("found something",       result_it != c.end(),   true);
        tester("found value is 313",    *result_it,             should_found);
        std::cout << "after result: ";
        print_container_over_iterator(c, result_it);
        // *result_it = 424242; // FAIL if a given container is a set.
        typename Container::reverse_iterator reverse_it = easyrfind(c, should_found);
        say("find 313 from the container REVERSELY...");
        tester("found something",       reverse_it != c.rend(), true);
        tester("found value is 313",    *reverse_it,            should_found);
        std::cout << "after result: ";
        print_container_over_riterator(c, reverse_it);
        say("find 1 from the container...");
        result_it = easyfind(c, should_not_found);
        tester("not found 1",           result_it == c.end(),   true);
    }
    say("(const test)");
    {
        const Container& cc = c;
        std::cout << "a const container is: ";
        print_container(cc);
        typename Container::const_iterator result_it = easyfind(cc, should_found);
        say("find 313 from the container...");
        tester("found something",       result_it != cc.end(),  true);
        tester("found value is 313",    *result_it,             should_found);
        std::cout << "after result: ";
        print_container_over_iterator(cc, result_it);
        // *result_it = 1; // error: cannot assign to return value because function 'operator*' returns a const value
        typename Container::const_reverse_iterator reverse_it = easyrfind(cc, should_found);
        say("find 313 from the container REVERSELY...");
        tester("found something",       reverse_it != cc.rend(), true);
        tester("found value is 313",    *reverse_it,            should_found);
        std::cout << "after result: ";
        print_container_over_riterator(cc, reverse_it);
        say("find 1 from the container...");
        result_it = easyfind(cc, should_not_found);
        tester("not found 1",           result_it == cc.end(),  true);
    }
}

int main() {
    const int args[] = {
        -10, 100, 313, -15926535, 313, 2
    };

    int should_found = 313;
    int should_not_found = 1;
    int n = 6;
    try {
        say("");
        say("[ vector ]");
        say("");
        typedef std::vector<int> Container;
        Container vec;
        for(int i = 0; i < n; i += 1) {
            vec.push_back(args[i]);
        }
        find_test(vec, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("");
        say("[ list ]");
        say("");
        typedef std::list<int> Container;
        Container lst;
        for(int i = 0; i < n; i += 1) {
            lst.push_back(args[i]);
        }
        find_test(lst, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("");
        say("[ set ]");
        say("");
        typedef std::set<int> Container;
        Container st;
        for(int i = 0; i < n; i += 1) {
            st.insert(args[i]);
        }
        find_test(st, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("");
        say("[ deque ]");
        say("");
        typedef std::deque<int> Container;
        Container deq;
        for(int i = 0; i < n; i += 1) {
            deq.push_back(args[i]);
        }
        find_test(deq, should_found, should_not_found);
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    return 0;
}
