#ifndef CPP08_MUTANTSTACK_HPP_
# define CPP08_MUTANTSTACK_HPP_

# include <iostream>
# include <stack>
# include <vector>
# include "Constants.hpp"

template <class T>
class MutantStack: public std::stack<T> {
    public:
        class iterator {
            public:
                iterator(const MutantStack<T>& ref, const std::size_t index):
                    ref_(ref), index_(index) {}

                iterator(const iterator& from):
                    ref_(from.ref_), index_(from.index_) {}

                virtual ~iterator() {}

                iterator&   operator=(const iterator &rhs) {
                    ref_ = rhs.ref_;
                    index_ = rhs.index_;
                    return *this;
                }

                T&          operator*() _NOEXCEPT {
                    return const_cast<T&>(ref_.vec_[index_]);
                }
                T           operator*() const _NOEXCEPT {
                    return ref_.vec_[index_];
                }

                iterator&   operator++() {
                    if (index_ != EndIndex) {
                        index_ -= 1;
                    }
                    return *this;
                }

                iterator    operator++(int) {
                    iterator rit = *this;
                    ++this;
                    return rit;
                }

                iterator&   operator--() {
                    if (index_ < ref_.size()) {
                        index_ += 1;
                    }
                    return *this;
                }

                iterator    operator--(int) {
                    iterator rit = *this;
                    --this;
                    return rit;
                }

                bool    isEnd(void) const {
                    return index_ == EndIndex;
                }

        bool    operator!=(const typename MutantStack<T>::iterator& rhs) {
            return !(*this == rhs);
        }

        bool    operator==(const typename MutantStack<T>::iterator& rhs) {
            return index_ == rhs.index_;
        }
            private:
                const MutantStack<T>&   ref_;
                std::size_t             index_;
        };

        MutantStack():
            std::stack<T>(), vec_(std::vector<T>()) {}

        MutantStack(const MutantStack<T>& from):
            std::stack<T>(from), vec_(from.vec_) {}

        virtual ~MutantStack() {}

        MutantStack<T>&   operator=(const MutantStack<T> &rhs) {
            *(static_cast<std::stack<T> *>(this)) = rhs;
            vec_ = rhs.vec_;
            return *this;
        }

        iterator    begin(void) const {
            std::size_t n = this->size() - 1;
            iterator it(*this, n);
            return it;
        }

        iterator    end(void) const {
            std::size_t n = -1;
            iterator it(*this, n);
            return it;
        }

        void        push(const T& v) {
            this->std::stack<T>::push(v);
            if (vec_.size() < this->size()) {
                std::cout
                    << Constants::kTextInfo
                    << "push " << v
                    << Constants::kTextReset << std::endl;
                vec_.push_back(v);
            } else {
                std::cout
                    << Constants::kTextInfo
                    << "assign " << v << " at " << this->size() - 1
                    << Constants::kTextReset << std::endl;
                vec_[this->size() - 1] = v;
            }
        }

        void        pop(void) {
            std::cout
                << Constants::kTextInfo
                << "pop"
                << Constants::kTextReset << std::endl;
            this->std::stack<T>::pop();
        }

    private:
        std::vector<T>   vec_;

        static const std::size_t EndIndex = -1;
};


#endif
