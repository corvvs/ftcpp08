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

class span {
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

        span(const unsigned int N);
        span(const span &from);
        span& operator=(const span &rhs);
        virtual ~span();

        void            addNumber(int item);
        unsigned int    shortestSpan(void) const;
        unsigned int    longestSpan(void) const;

    private:
        span();

        unsigned int    N_;
        unsigned int    added_;
        std::set<int>   items_;
        unsigned int    shortest_span_;
        int             stored_max_;
        int             stored_min_;
        bool            switched_;
};

#endif
