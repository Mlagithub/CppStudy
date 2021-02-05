

#include <type_traits>
#include <iostream>
#include <string>

template <typename T>
typename std::enable_if_t<std::is_integral_v<T>> sfinaf(T rhs) {
    std::cout << "Call int " << rhs << '\n';
}

template <typename T>
typename std::enable_if_t<std::is_floating_point_v<T>> sfinaf(T rhs) {
    std::cout << "Call float " << rhs << '\n';
}

template <class T>
auto f(const T &t) -> std::enable_if_t<std::is_integral_v<T>, bool> {
    return true;
}

template <class T>
auto f(const T &t) -> std::enable_if_t<!std::is_integral_v<T>, std::string> {
    return std::string("No");
}