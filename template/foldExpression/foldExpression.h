

#pragma once

#include <iostream>

namespace Detail {
// print
template <typename T>
void process_(T &&args) {
    std::cout << args << '\n';
}


// predicate if true
template <typename T>
bool pred_(T &&args) {
    return args ? true : false;
}

// predicate if true
template <typename T>
bool biggerThanThree_(T &&args) {
    return args > 3 ? true : false;
}
} // namespace Detail




namespace FoldExpression {

// precess every element of a pack
template <typename... Args>
void lookup(Args &&... args) {
    (Detail::process_(std::move(args)), ...);
}

// reverse precess every element of a pack
template <typename... Args>
void reverseLookup(Args &&... args) {
    int dummy;
    (dummy = ... = (Detail::process_(std::move(args)), 0));
}

// process element of first predicted true
template <typename... Args>
void firstPred(Args &&... args) {
    ((Detail::biggerThanThree_(std::move(args)) ? (Detail::process_(std::move(args)), false) : true) && ...);
}

// if any element of a pack is true
template <typename... Args>
bool any(Args &&... args) {
    return ((Detail::pred_(std::move(args)) || ...));
}

// first element 
template<typename ... Args>
auto firstElement(Args&& ... args) ->std::common_type_t<decltype(args)...>{
    std::common_type_t<decltype(args)...> rst;
    ((rst = args, true) || ...);
    return rst;
}

// last element
template <typename... Args>
auto lastElement(Args &&... args) -> std::common_type_t<decltype(args)...> {
    std::common_type_t<decltype(args)...> rst;
    ((rst = args, true) && ...);
    return rst;
}

// nth element
template <typename... Args>
auto nthElement(const int N, Args &&... args) -> std::common_type_t<decltype(args)...> {
    std::common_type_t<decltype(args)...> rst;
    int i = 0;
    ((i++ == N ? (rst = args, true) : false) || ...);
    return rst;
}

// min element
template <typename... Args>
auto minElement(const int N, Args &&... args) -> std::common_type_t<decltype(args)...> {
    std::common_type_t<decltype(args)...> rst;
    rst = (args, ...);
    ((rst > args ? (rst = args) : 0), ...);
    return rst;
}

} // namespace FoldExpression