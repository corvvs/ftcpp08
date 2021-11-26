#include "span.hpp"

Span::IllegalConstructionError::IllegalConstructionError(const char *_message):
    std::runtime_error(_message) {}
Span::CapacityFullError::CapacityFullError(const char *_message):
    std::runtime_error(_message) {}
Span::NoSpanError::NoSpanError(const char *_message):
    std::runtime_error(_message) {}

Span::Span() {
    throw Span::IllegalConstructionError("default constructor is not allowed");
}

Span::Span(const unsigned int N):
    N_(N), added_(0), items_(std::set<int>()),
    shortest_span_(UINT_MAX),
    stored_max_(INT_MIN), stored_min_(INT_MAX)
    {}

Span::Span(const Span &from):
    N_(from.N_), added_(from.added_), items_(from.items_),
    shortest_span_(from.shortest_span_),
    stored_max_(from.stored_max_), stored_min_(from.stored_min_)
    {}

Span&   Span::operator=(const Span &rhs) {
    if (this == &rhs) {
        return *this;
    }
    N_ = rhs.N_;
    added_ = rhs.added_;
    items_ = std::set<int>(rhs.items_);
    shortest_span_ = rhs.shortest_span_;
    stored_max_ = rhs.stored_max_;
    stored_min_ = rhs.stored_min_;
    return *this;
}

Span::~Span() {}

unsigned int    Span::getN(void) const {
    return N_;
}

unsigned int    Span::getAdded(void) const {
    return added_;
}

void            Span::addNumber(int item) {
    if (N_ <= added_) {
        throw Span::CapacityFullError("this object is full");
    }
    if (shortest_span_ > 0) {
        std::set<int>::iterator itend = items_.end();
        if (items_.find(item) != itend) {
            shortest_span_ = 0;
        } else {
            std::set<int>::iterator lb = items_.lower_bound(item);
            std::set<int>::iterator be = items_.begin();
            std::set<int>::iterator ed = items_.end();
            if (lb != ed) {
                unsigned int span = *lb - item;
                if (span < shortest_span_) {
                    shortest_span_ = span;
                }
            }
            if (lb != be) {
                --lb;
                unsigned int span = item - *lb;
                if (span < shortest_span_) {
                    shortest_span_ = span;
                }
            }
            items_.insert(item);
        }
    }
    added_ += 1;
    if (stored_max_ < item) {
        stored_max_ = item;
    }
    if (stored_min_ > item) {
        stored_min_ = item;
    }
}

unsigned int    Span::longestSpan(void) const {
    if (added_ < 2) {
        throw Span::NoSpanError("there is no Span");
    }
    return stored_max_ - stored_min_;
}

unsigned int    Span::shortestSpan(void) const {
    if (added_ < 2) {
        throw Span::NoSpanError("there is no Span");
    }
    return shortest_span_;
}
