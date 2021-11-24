#ifndef CPP08_SPAN_HPP_
# define CPP08_SPAN_HPP_

# include <iostream>
# include <set>
# include <algorithm>
# include <exception>
# include <stdexcept>
# include <cmath>
# include <cstdlib>
# include <climits>
# include "Constants.hpp"

class Span {
    public:
        class IllegalConstructionError: public std::runtime_error {
            public:
                IllegalConstructionError(const char *_message);
        };
        class CapacityFullError: public std::runtime_error {
            public:
                CapacityFullError(const char *_message);
        };
        class NoSpanError: public std::runtime_error {
            public:
                NoSpanError(const char *_message);
        };

        Span(const unsigned int N);
        Span(const Span &from);
        Span& operator=(const Span &rhs);
        virtual ~Span();

        void            addNumber(int item);

        template < class Iterator >
        void            addNumbers(
            Iterator begin,
            Iterator end
        ) {
            Iterator it = begin;
            for (; it != end; ++it) {
                int n = *it;
                addNumber(n);
            }
        }

        unsigned int    shortestSpan(void) const;
        unsigned int    longestSpan(void) const;

    private:
        Span();

        unsigned int    N_;
        unsigned int    added_;
        std::set<int>   items_;
        unsigned int    shortest_span_;
        int             stored_max_;
        int             stored_min_;
};

#endif
