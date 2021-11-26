#ifndef CPP08_EASYFIND_HPP_
# define CPP08_EASYFIND_HPP_

# include <algorithm>

template< class T, class A >
typename T::iterator        absfind(T& arr, const A& value) {
    typename T::iterator ibegin = arr.begin();
    typename T::iterator iend = arr.end();
    typename T::iterator result = std::find(ibegin, iend, value);
    return result;
}

template< class T, class A >
typename T::const_iterator  absfind(const T& arr, const A& value) {
    typename T::const_iterator ibegin = arr.begin();
    typename T::const_iterator iend = arr.end();
    typename T::const_iterator result = std::find(ibegin, iend, value);
    return result;
}

template< class T >
typename T::iterator        easyfind(T& arr, const int value) {
    typename T::iterator result = absfind(arr, value);
    return result;
}

template< class T >
typename T::const_iterator  easyfind(const T& arr, const int value) {
    typename T::const_iterator result = absfind(arr, value);
    return result;
}

#endif
