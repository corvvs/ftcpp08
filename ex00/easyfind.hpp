#ifndef CPP07_EASYFIND_HPP_
# define CPP07_EASYFIND_HPP_

template<class T, class A>
int medfind(T container, A value) {
    for (int i = 0; 0 <= i && i < static_cast<int>(container.size()); i += 1) {
        if (container[i] == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
int easyfind(T container, int value) {
    return medfind<T, int>(container, value);
}

#endif
