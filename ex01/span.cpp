#include "span.hpp"

bool    additionWillOverflow(int a, int b) {
    if (a > 0 && b > 0 && a > INT_MAX - b) {
        return true;
    }
    if (a < 0 && b < 0 && a < INT_MIN - b) {
        return true;
    }
    return false;
}

bool    subtractionWillOverflow(int a, int b) {
    if (a > 0 && b < 0 && a > INT_MAX + b) {
        return true;
    }
    if (a < 0 && b > 0 && a < INT_MIN + b) {
        return true;
    }
    return false;
}

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
    stored_max_(INT_MIN), stored_min_(INT_MAX), switched_(false)
    {}

span::span(const span &from):
    N_(from.N_), added_(from.added_), items_(from.items_),
    shortest_span_(from.shortest_span_),
    stored_max_(from.stored_max_), stored_min_(from.stored_min_), switched_(false)
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
    std::set<int>::iterator itend = items_.end();
    if (items_.find(item) != itend) {
        shortest_span_ = 0;
    } else if (switched_) {
        int ss = static_cast<int>(shortest_span_);
        for (int i = 1; i < ss; i += 1) {
            if (!additionWillOverflow(item, i) && items_.find(item + i) != itend) {
                shortest_span_ = i;
                break;
            }
            if (!subtractionWillOverflow(item, i) && items_.find(item - i) != itend) {
                shortest_span_ = i;
                break;
            }
        }
        items_.insert(item);
    } else {
        std::set<int>::iterator itbegin = items_.begin();
        for (std::set<int>::iterator it = itbegin; it != itend; ++it) {
            unsigned int span = *it > item ? *it - item : item - *it;
            if (span < shortest_span_) {
                shortest_span_ = span;
            }
        }
        items_.insert(item);
    }
    added_ += 1;
    if (stored_max_ < item) {
        // std::cout
        //     << Constants::kTextInfo
        //     << "max: " << stored_max_ << " -> " << item
        //     << Constants::kTextReset << std::endl;
        stored_max_ = item;
    }
    if (stored_min_ > item) {
        // std::cout
        //     << Constants::kTextInfo
        //     << "min: " << stored_min_ << " -> " << item
        //     << Constants::kTextReset << std::endl;
        stored_min_ = item;
    }
    if (!switched_ && shortest_span_ < INT_MAX && shortest_span_ * std::log2(added_) < added_) {
        switched_ = true;
        std::cout
            << Constants::kTextInfo
            << added_ << ": algorithm switched"
            << Constants::kTextReset << std::endl;
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
