
#pragma once

#include "header.h"

void variant_visit() {

    std::variant<int, double, std::string> x, y;

    // assign value
    x = 1;
    y = "1.0";

    // use visit(func, variant) to process type of variant element.
    // func is a template function process all type of variant

    // call with class member func
    std::visit(Func(), y);

    // call with lambda func
    // need c++14 generic lambda feature
    std::visit([](const auto &v) {
        std::cout << "call from Lambda, value is " << v << '\n';
    }, x);

    // different type need different process
    // class member func
    x = "string";
    std::visit(Func1(), x);
    x = 2.3;
    std::visit(Func1(), x);

    // different type need different process
    // lambda func
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if
            constexpr(std::is_same_v<T, int>) {
                std::cout << "int with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, double>) {
                std::cout << "double with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, std::string>) {
                std::cout << "std::string with value " << std::quoted(arg)
                          << '\n';
            }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
    }, x);

    x = "now value is 234";
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if
            constexpr(std::is_same_v<T, int>) {
                std::cout << "int with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, double>) {
                std::cout << "double with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, std::string>) {
                std::cout << "std::string with value " << std::quoted(arg)
                          << '\n';
            }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
    }, x);
}