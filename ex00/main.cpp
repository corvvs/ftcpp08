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
int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout
            << Constants::kTextWarning
            << "least 2 arguments needed"
            << Constants::kTextReset << std::endl;
        return 1;
    }
    int m = std::atoi(argv[1]);
    int n = argc - 2;
    try {
        say("[ vector ]");
        std::vector<int> arr(n);
        for(int i = 0; i < n; i += 1) {
            arr[i] = std::atoi(argv[i + 2]);
        }

        int result = easyfind(arr, m);
        std::cout << result << std::endl;
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ list ]");
        std::list<int> list;
        for(int i = 0; i < n; i += 1) {
            list.push_back(std::atoi(argv[i + 2]));
        }
        int result = easyfind(list, m);
        std::cout << result << std::endl;
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ set ]");
        std::set<int> set;
        for(int i = 0; i < n; i += 1) {
            set.insert(std::atoi(argv[i + 2]));
        }
        int result = easyfind(set, m);
        std::cout << result << std::endl;
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        say("[ deque ]");
        std::deque<int> deq;
        for(int i = 0; i < n; i += 1) {
            deq.push_back(std::atoi(argv[i + 2]));
        }
        int result = easyfind(deq, m);
        std::cout << result << std::endl;
    } catch(std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    return 0;
}
