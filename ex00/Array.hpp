#ifndef CPP07_ARRAY_HPP_
# define CPP07_ARRAY_HPP_

# include <iostream>
# include <exception>
# include <stdexcept>

template <class T>
class Array {
    private:
        unsigned int    cap_; // 0 <= size_ <= cap_
        unsigned int    size_;
        T*              body_;

    public:
        // ** Constructor **
        Array(unsigned int size = 0):
            cap_(size),
            size_(size),
            body_(new T[size_]())
            {}

        // ** Copy Constructor **
        Array(const Array &from):
            cap_(from.size_),
            size_(from.size_),
            body_(new T[from.size_]())
        {
            for (unsigned int i = 0; i < size_; i += 1) {
                body_[i] = from.body_[i];
            }
        }

        // ** Operator Overloaded **
        Array& operator=(const Array &rhs) {
            if (this == &rhs) {
                return *this;
            }
            if (cap_ < rhs.cap_) {
                // lhs is smaller than rhs: reallocation needed
                T *temp = rhs.body_ ? new T[rhs.cap_]() : NULL;
                delete[] body_;
                body_ = temp;
                cap_ = rhs.cap_;
            } else {
                // lhs is not smaller than rhs: no allocation neeeded
            }
            size_ = rhs.size_;
            if (body_) {
                for (unsigned int i = 0; i < size_; i += 1) {
                    body_[i] = rhs.body_[i];
                }
            }
            return *this;
        }

        T& operator [](std::size_t i) {
            if (static_cast<std::size_t>(size_) <= i) {
                throw std::out_of_range("index out of range");
            }
            if (!body_) {
                throw std::runtime_error("internal error");
            }
            return body_[i];
        }

        const T& operator [](std::size_t i) const {
            if (static_cast<std::size_t>(size_) <= i) {
                throw std::out_of_range("index out of range");
            }
            if (!body_) {
                throw std::runtime_error("internal error");
            }
            return body_[i];
        }

        // ** Destructor **
        virtual ~Array() {
            delete[] body_;
        }

        // ** Member Functions **
        unsigned int    size(void) const {
            return getSize();
        }

        unsigned int    getSize(void) const {
            return size_;
        }

        void            iter(void (*func)(const T&)) {
            if (!func) {
                return;
            }
            if (!body_) {
                return;
            }
            for (std::size_t i = 0; i < size_; i += 1) {
                func(body_[i]);
            }
        }
};

template <class T>
std::ostream&   operator<<(std::ostream& stream, const Array<T>& value) {
    stream << "[";
    for (unsigned int i = 0; i < value.size(); i += 1) {
        if (0 < i) {
            stream << ", ";
        }
        stream << value[i];
    }
    stream << "]";
    return stream;
}

#endif
