#ifndef CPP08_EASYFIND_HPP_
# define CPP08_EASYFIND_HPP_

# include <algorithm>

template< class T, class A >
typename T::iterator absfind(T& arr, A value) {
    typename T::iterator ibegin = arr.begin();
    typename T::iterator iend = arr.end();
    typename T::iterator result = std::find(ibegin, iend, value);
    return result;
}

template< class T >
typename T::iterator easyfind(T& arr, int value) {
    return absfind(arr, value);
}

#endif
