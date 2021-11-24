#ifndef CPP08_MUTANTSTACK_HPP_
# define CPP08_MUTANTSTACK_HPP_

# include <iostream>
# include <stack>
# include <deque>
# include "Constants.hpp"

template <class T, class _MContainer = std::deque<T> >
class MutantStack: public std::stack<T, _MContainer> {
    public:
        typedef typename _MContainer::iterator                  iterator;
        typedef typename _MContainer::const_iterator            const_iterator;
        typedef typename _MContainer::reverse_iterator          reverse_iterator;
        typedef typename _MContainer::const_reverse_iterator    const_reverse_iterator;

        MutantStack():
            std::stack<T, _MContainer>() {}
        MutantStack(const MutantStack<T, _MContainer>& from):
            std::stack<T, _MContainer>(from) {}

        virtual ~MutantStack() {}

        iterator                begin(void) {
            _MContainer& mc = this->c;
            return mc.begin();
        }

        iterator                end(void) {
            _MContainer& mc = this->c;
            return mc.end();
        }

        const_iterator          begin(void) const {
            const _MContainer& mc = this->c;
            return mc.begin();
        }

        const_iterator          end(void) const {
            const _MContainer& mc = this->c;
            return mc.end();
        }

        reverse_iterator        rbegin(void) {
            _MContainer& mc = this->c;
            return mc.rbegin();
        }

        reverse_iterator        rend(void) {
            _MContainer& mc = this->c;
            return mc.rend();
        }

        const_reverse_iterator  rbegin(void) const {
            const _MContainer& mc = this->c;
            return mc.rbegin();
        }

        const_reverse_iterator  rend(void) const {
            const _MContainer& mc = this->c;
            return mc.rend();
        }
};


#endif
