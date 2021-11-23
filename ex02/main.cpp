#include <iostream>
#include "mutantstack.hpp"
#include "Constants.hpp"
#include <exception>
#include <stdexcept>

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

void pdf_test(void) {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    mstack.pop();
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    mstack.push(3);
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    mstack.push(5);
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    mstack.push(737);
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    //[...]
    mstack.push(0);
    std::cout << mstack.top() << " " << mstack.size() << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    std::cout << *it << std::endl;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);    
}

int main() {
    MutantStack<int> ms;
    ms.push(1);
    ms.push(2);
    ms.push(3);
    ms.push(4);
    try {
        std::cout << ms.top() << std::endl;
        ms.pop();
        std::cout << ms.top() << std::endl;
        ms.pop();
        std::cout << ms.top() << std::endl;
        ms.pop();
        std::cout << ms.top() << std::endl;
        ms.pop();
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
    try {
        pdf_test();
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}
