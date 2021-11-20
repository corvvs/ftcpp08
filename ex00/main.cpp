#include <iostream>
#include <cstdlib>
#include "easyfind.hpp"
#include "Array.hpp"
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
    Array<int> arr(n);
    for(int i = 0; i < n; i += 1) {
        arr[i] = std::atoi(argv[i + 2]);
    }
    std::cout
        << Constants::kTextInfo
        << "find <" << m << "> from array:" << std::endl
        << arr
        << Constants::kTextReset << std::endl;
    int j = easyfind(arr, m);
    if (0 <= j) {
        std::cout
            << Constants::kTextInfo
            << "found: arr[" << j << "] = " << arr[j]
            << Constants::kTextReset << std::endl;
    } else {
        std::cout
            << Constants::kTextWarning
            << "not found"
            << Constants::kTextReset << std::endl;
    }
    return 0;
}
