#ifndef CPP08_EASYFIND_HPP_
# define CPP08_EASYFIND_HPP_

# include <algorithm>

template< class T, class A >
int absfind(T arr, A value) {
    typename T::iterator ibegin = std::begin(arr);
    typename T::iterator iend = std::end(arr);
    typename T::iterator result = std::find(ibegin, iend, value);
    if (result == iend) {
        throw std::runtime_error("not found");
    }
    return *result;
}

template< class T >
int easyfind(T arr, int value) {
    return absfind(arr, value);
}

#endif
