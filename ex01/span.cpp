#include "span.hpp"

span::IllegalConstructionError::IllegalConstructionError(const char *_message):
    std::runtime_error(_message) {}
span::CapacityFullError::CapacityFullError(const char *_message):
    std::runtime_error(_message) {}
span::NoSpanError::NoSpanError(const char *_message):
    std::runtime_error(_message) {}

span::span() {
    throw span::IllegalConstructionError("default constructor is not allowed");
}

span::span(const unsigned int N):
    N_(N), added_(0), items_(std::set<int>()),
    shortest_span_(UINT_MAX),
    stored_max_(INT_MIN), stored_min_(INT_MAX)
    {}

span::span(const span &from):
    N_(from.N_), added_(from.added_), items_(from.items_),
    shortest_span_(from.shortest_span_),
    stored_max_(from.stored_max_), stored_min_(from.stored_min_)
    {}

span& span::operator=(const span &rhs) {
    N_ = rhs.N_;
    added_ = rhs.added_;
    items_ = std::set<int>(rhs.items_);
    shortest_span_ = rhs.shortest_span_;
    stored_max_ = rhs.stored_max_;
    stored_min_ = rhs.stored_min_;
    return *this;
}

span::~span() {}

void    span::addNumber(int item) {
    if (N_ <= added_) {
        throw span::CapacityFullError("this object is full");
    }
    if (shortest_span_ < added_) {
        std::set<int>::iterator itend = items_.end();
        if (items_.find(item) != itend) {
            shortest_span_ = 0;
        } else {
            for (unsigned int i = 1; i < shortest_span_; i += 1) {
                if (items_.find(item + i) != itend || items_.find(item - i) != itend) {
                    shortest_span_ = i;
                }
            }
            items_.insert(item);
        }
    } else {
        std::set<int>::iterator itbegin = items_.begin();
        std::set<int>::iterator itend   = items_.end();
        for (std::set<int>::iterator it = itbegin; it != itend; ++it) {
            unsigned int span = item < *it ? *it - item : item - *it;
            if (span < shortest_span_) {
                shortest_span_ = span;
            }
        }
    }
    items_.insert(item);
    added_ += 1;
    if (stored_max_ < item) {
        stored_max_ = item;
    }
    if (stored_min_ > item) {
        stored_min_ = item;
    }
}

unsigned int    span::longestSpan(void) const {
    if (added_ < 2) {
        throw span::NoSpanError("there is no span");
    }
    return stored_max_ - stored_min_;
}

unsigned int    span::shortestSpan(void) const {
    if (added_ < 2) {
        throw span::NoSpanError("there is no span");
    }
    return shortest_span_;
}
