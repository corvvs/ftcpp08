#include <iostream>
#include <sstream>
#include "mutantstack.hpp"
#include "Constants.hpp"
#include "mutantstack.hpp"
#include "Constants.hpp"
#include <deque>
#include <vector>
#include <list>
#include <exception>
#include <stdexcept>

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

template <class MContainer>
void    print_stack(MutantStack<int, MContainer > mstack, std::ostream& ost) {
    ost << "[";
    typename MutantStack<int, MContainer >::iterator it = mstack.begin();
    for (; it != mstack.end(); ++it) {
        if (it != mstack.begin()) {
            ost << ", ";
        }
        ost << *it;
    }
    ost << "]" << std::endl;
}

template <class Iterator>
void    print_by_iterator(
    Iterator& begin,
    Iterator& end,
    std::ostream& ost
) {
    Iterator it = begin;
    ost << "[";
    for (; it != end; ++it) {
        if (it != begin) {
            ost << ", ";
        }
        ost << *it;
    }
    ost << "]";
}

template <class Iterator>
std::string stringify_by_iterator(
    Iterator begin,
    Iterator end
) {
    std::stringstream ss;
    print_by_iterator(begin, end, ss);
    return ss.str();
}

template <class MContainer>
void    pdf_test(void) {
    std::string result_str;
    try {
        typedef MutantStack<int, MContainer > MS;
        MS mstack;
        result_str = stringify_by_iterator(mstack.begin(), mstack.end());
        tester("mstack is empty?", result_str, std::string("[]"));
        mstack.push(5);
        mstack.push(17);
        tester("stack size is 2?", mstack.size(), 2ul);
        tester("stack top is 17?", mstack.top(), 17);
        mstack.pop();
        tester("stack size is 1?", mstack.size(), 1ul);
        tester("stack top is 5?", mstack.top(), 5);
        mstack.push(3);
        tester("stack size is 2?", mstack.size(), 2ul);
        tester("stack top is 3?", mstack.top(), 3);
        mstack.push(5);
        tester("stack size is 3?", mstack.size(), 3ul);
        tester("stack top is 5?", mstack.top(), 5);
        mstack.push(737);
        tester("stack size is 4?", mstack.size(), 4ul);
        tester("stack top is 737?", mstack.top(), 737);
        //[...]
        mstack.push(0);
        tester("stack size is 5?", mstack.size(), 5ul);
        tester("stack top is 0?", mstack.top(), 0);
        typename MS::iterator it = mstack.begin();
        const typename MS::iterator cit = mstack.begin();
        typename MS::iterator ite = mstack.end();
        tester("iterator designates 5(bottom of stack)?", *it, 5);
        tester("begin() == begin()?", it == mstack.begin(), true);
        tester("begin() == const begin()?", it == cit, true);
        it++;
        tester("begin() + 1 == begin()?", it == mstack.begin(), false);
        tester("begin() + 1 == const begin()?", it == cit, false);
        it--;
        tester("begin() + 1 - 1 == begin()?", it == mstack.begin(), true);
        tester("begin() + 1 - 1 == const begin()?", it == cit, true);
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
        --it;
        tester("it designates 0?", *it, 0);
        tester("it designates top of stack?", *it, mstack.top());
        // mstack is:
        // bottom [5 3 5 737 0] top
        result_str = stringify_by_iterator(mstack.begin(), mstack.end());
        tester("mstack is fulled?", result_str, std::string("[5, 3, 5, 737, 0]"));
        // mstack.top() = 1;
        *it = 1;
        std::cout << "assigned 1 into it" << std::endl;
        result_str = stringify_by_iterator(mstack.begin(), mstack.end());
        tester("stack top is changed?", result_str, std::string("[5, 3, 5, 737, 1]"));
        tester("it designates 1?", *it, 1);
        tester("stack top is 1?", mstack.top(), 1);
        it = mstack.end();
        --it;
        *it = 2;
        tester("it designates 2?", *it, 2);
        tester("stack top is 2?", mstack.top(), 2);
        while (it != cit)
        {
            std::cout << *it << std::endl;
            --it;
        }
        tester("it designates 5?", *it, 5);
        result_str = stringify_by_iterator(mstack.begin(), mstack.end());
        tester("stack is", result_str, std::string("[5, 3, 5, 737, 2]"));
        result_str = stringify_by_iterator(mstack.rbegin(), mstack.rend());
        tester("in reversed", result_str, std::string("[2, 737, 5, 3, 5]"));
        std::stack<int, MContainer> s(mstack);
        tester("std::stack top is 5?", s.top(), 2);
        tester("std::stack size is 5?", s.size(), 5ul);
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}

template <class MContainer>
void    comparation_test(void) {
    std::string result_str;
    try {
        typedef MutantStack<int, MContainer > MS;
        MS ms1;
        typename MS::iterator b1 = ms1.begin();
        typename MS::iterator e1 = ms1.end();
        {
            MS ms2 = ms1;
            std::cout << &ms1 << " " << &ms2 << " " << (ms1 == ms2) << std::endl;
            b1 = ms1.begin();
            e1 = ms1.end();
            typename MS::iterator b2 = ms2.begin();
            typename MS::iterator e2 = ms2.end();
            tester(" ms1(0).begin() == ms1(0).begin()",    b1  ==   b1,  true);
            tester(" ms1(0).begin() == ms1(0).end()",      b1  ==   e1,  true);
            tester(" ms1(0).end()   == ms1(0).end()",      e1  ==   e1,  true);

            tester("(should be ok for deque or vector) ms1(0).begin() == ms2(0).begin()",    b1  ==   b2,  true, true);
            tester("(should be ok for deque or vector) ms1(0).begin() == ms2(0).end()",      b1  ==   e2,  true, true);
            tester("(should be ok for deque or vector) ms1(0).end()   == ms2(0).end()",      e1  ==   e2,  true, true);
            tester(" ms2(0).begin() == ms2(0).end()",      b2  ==   e2,  true);
            tester("(should be ok for deque or vector)&ms1(0).begin() == &ms2(0).begin()", &(*b1) == &(*b2), true, true);
            tester("(should be ok for deque or vector)&ms1(0).begin() == &ms2(0).end()",   &(*b1) == &(*e2), true, true);
            tester("(should be ok for deque or vector)&ms1(0).end()   == &ms2(0).end()",   &(*e1) == &(*e2), true, true);
            ms1.push(1);
            std::cout << "pushed 1 into ms1" << std::endl;
            b1 = ms1.begin();
            e1 = ms1.end();

            tester(" ms1(1).begin() == ms1(1).begin()",    b1  ==   b1,  true);
            tester(" ms1(1).begin() == ms1(1).end()",      b1  ==   e1,  false);
            tester(" ms1(1).end()   == ms1(1).end()",      e1  ==   e1,  true);

            tester(" ms1(1).begin() == ms2(0).begin()",    b1  ==   b2,  false);
            tester(" ms1(1).begin() == ms2(0).end()",      b1  ==   e2,  false);
            tester(" ms1(1).end()   == ms2(0).end()",      e1  ==   e2,  false);
            tester(" ms2(0).begin() == ms2(0).end()",      b2  ==   e2,  true);

            tester("&ms1(1).begin() == &ms2(0).begin()", &(*b1) == &(*b2), false);
            tester("&ms1(1).begin() == &ms2(0).end()",   &(*b1) == &(*e2), false);
            tester("&ms1(1).end()   == &ms2(0).end()",   &(*e1) == &(*e2), false);
            std::cout << &*e1 << " " << &*e2 << std::endl;
            result_str = stringify_by_iterator(ms1.begin(), ms1.end());
            tester("m1 is", result_str, std::string("[1]"));
            result_str = stringify_by_iterator(ms2.begin(), ms2.end());
            tester("m2 is", result_str, std::string("[]"));
            MS ms3;
            typename MS::iterator s3 = ms3.begin();
            typename MS::iterator e3 = ms3.end();
            tester("(should be ok for deque or vector) ms2(0).end()   == ms3(0).end()",      e2  ==   e3,  true, true);
            tester(" ms3(0).start() == ms3(0).end()",      s3  ==   e3,  true);

            ms1.pop();
            std::cout << "popped from ms1" << std::endl;
            b1 = ms1.begin();
            e1 = ms1.end();
            tester(" ms1(0).empty()",                      ms1.empty(),  true);
            tester(" ms1(0).begin() == ms1(0).end()",      b1  ==   e1,  true);
            tester(" ms1(0).end()   == ms2(0).end()",      e1  ==   e2,  false);
            tester("&ms1(0).begin() == &ms2(0).begin()", &(*b1) == &(*b2), false);
            tester("&ms1(0).begin() == &ms2(0).end()",   &(*b1) == &(*e2), false);
            tester("&ms1(0).end()   == &ms2(0).end()",   &(*e1) == &(*e2), false);
        }
        b1 = ms1.begin();
        e1 = ms1.end();
        tester(" ms1(1).begin() == ms1(1).begin()",  b1 == b1, true);
        // say("[ contrast: vector ]");
        // std::vector<int> vec(0);
        // tester("vector(0).start() == vector(0).end()", vec.begin() == vec.end(), true);
        // vec.push_back(1);
        // tester("vector(1).start() == vector(1).end()", vec.begin() == vec.end(), false);
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}

template <class MContainer>
void    iterator_test(void) {
    std::string result_str;
    try {
        typedef MutantStack<int, MContainer > MS;
        MS vstack;
        vstack.push(3);
        vstack.push(1);
        vstack.push(4);
        vstack.push(1);
        vstack.push(5);
        vstack.push(9);
        vstack.push(2);
        {
            typename MS::iterator be;
            typename MS::iterator en;
            typename MS::reverse_iterator rb;
            typename MS::reverse_iterator re;
            be = vstack.begin();
            en = vstack.end();
            rb = vstack.rbegin();
            re = vstack.rend();
            result_str = stringify_by_iterator(be, en);
            tester("print normally", result_str, std::string("[3, 1, 4, 1, 5, 9, 2]"));
            result_str = stringify_by_iterator(rb, re);
            tester("print reversely", result_str, std::string("[2, 9, 5, 1, 4, 1, 3]"));
            *be = 4;
            result_str = stringify_by_iterator(be, en);
            tester("print normally", result_str, std::string("[4, 1, 4, 1, 5, 9, 2]"));
            *rb = 9;
            result_str = stringify_by_iterator(rb, re);
            tester("print reversely", result_str, std::string("[9, 9, 5, 1, 4, 1, 4]"));
        }
        const MS cstack(vstack);
        {
            typename MS::const_iterator be = cstack.begin();
            typename MS::const_iterator en = cstack.end();
            typename MS::const_reverse_iterator rb = cstack.rbegin();
            typename MS::const_reverse_iterator re = cstack.rend();
            result_str = stringify_by_iterator(be, en);
            tester("print normally", result_str, std::string("[4, 1, 4, 1, 5, 9, 9]"));
            result_str = stringify_by_iterator(rb, re);
            tester("print reversely", result_str, std::string("[9, 9, 5, 1, 4, 1, 4]"));
        }
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}

int     main() {
    say("[ PDF test by deque ]");
    pdf_test<std::deque<int> >();
    say("[ PDF test by vector ]");
    pdf_test<std::vector<int> >();
    say("[ PDF test by list ]");
    pdf_test<std::list<int> >();

    say("[ Iterator test by deque ]");
    iterator_test<std::deque<int> >();
    say("[ Iterator test by vector ]");
    iterator_test<std::vector<int> >();
    say("[ Iterator test by list ]");
    iterator_test<std::list<int> >();

    say("[ comparation test by deque ]");
    comparation_test<std::deque<int> >();
    say("[ comparation test by vector ]");
    comparation_test<std::vector<int> >();
    say("[ comparation test by list ]");
    comparation_test<std::list<int> >();
}
